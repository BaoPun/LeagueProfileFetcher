#include "./staticData.h"

StaticData::StaticData(){
    this->version = "";
}

/**
 * @brief Getter to retrieve the version recorded by the static data
 * @return the version recorded by the static data
 */
string StaticData::get_version(){
    return this->version;
}

/**
 * @brief Getter to retrieve the champion's name given the key
 * @param the numerical key
 * @return the champion name from the champion_data mapping.
 */
QString StaticData::get_champion_name_by_key(int key){
    return this->champion_data[key].get_name();
}

/**
 * @brief Getter to retrieve the champion's immage url given the key
 * @param the numerical key
 * @return the champion's image url from the champion_data mapping.
 */
QString StaticData::get_champion_image_url_by_key(int key){
    return this->champion_data[key].get_image_url();
}

/**
 * @brief Getter to retrieve the champion's spell url given the key
 * @param the numerical key
 * @return the champion's spell url from the champion_data mapping
 */
QString StaticData::get_champion_spell_url_by_key(int key){
    return this->champion_data[key].get_spell_url();
}

string StaticData::get_summoner_spell_name_by_key(int key){
    return this->summoner_spell_data[key]["summonerSpellName"];
}

string StaticData::get_summoner_spell_description_by_key(int key){
    return this->summoner_spell_data[key]["summonerSpellDescription"];
}

/**
 * @brief Set the latest version
 * @param version - update the static data's version with the parameter
 */
void StaticData::set_version(string version, PostgresDatabase* database){
    this->version = version;
    if(database != nullptr && QString::fromStdString(this->version) != database->get_version())
        database->update_version(QString::fromStdString(version));
}

/**
 * @brief Set the champion data.
 * @param json - json object with the data key
 * @param database - database pointer that will handle any queries and transactions
 */
void StaticData::set_champion_data(QJsonObject json, PostgresDatabase* database){
    // First, determine if we have to cleanse the database
    bool champion_data_needs_update = database != nullptr && json.keys().length() != database->get_num_champions_database();
    if(champion_data_needs_update){
        cout << "Outdated version detected.  Cleansing old champion data from the database..." << endl;
        database->delete_champions();
    }

    //QJsonDocument doc;
    //doc.setObject(json);
    //cout << "Json mastery data: " << doc.toJson(QJsonDocument::Indented).toStdString() << endl;

    QString values;
    foreach(QString key, json.keys()){
        // For some reason, RIOT uses Wukong's name as MonkeyKing in their API.
        // Properly change the Wukong, but the URL for the image MUST remain as MonkeyKing
        if(key == "MonkeyKing")
            this->champion_data[json[key].toObject()["key"].toString().toInt()].set_name("Wukong");//["championName"] = "Wukong";
        else
            this->champion_data[json[key].toObject()["key"].toString().toInt()].set_name(key);//["championName"] = "Wukong";// = key.toStdString();

        // Add the id, image_url & spell_url, title, lore, and resource type
        this->champion_data[json[key].toObject()["key"].toString().toInt()].set_id(json[key].toObject()["id"].toInt());
        this->champion_data[json[key].toObject()["key"].toString().toInt()].set_image_url(QString::fromStdString("http://ddragon.leagueoflegends.com/cdn/" + this->version + "/img/champion/" + key.toStdString() + ".png"));
        this->champion_data[json[key].toObject()["key"].toString().toInt()].set_spell_url(QString::fromStdString("https://ddragon.leagueoflegends.com/cdn/" + this->version + "/data/en_US/champion/" + key.toStdString() + ".json"));
        this->champion_data[json[key].toObject()["key"].toString().toInt()].set_title(json[key].toObject()["title"].toString());
        this->champion_data[json[key].toObject()["key"].toString().toInt()].set_lore(json[key].toObject()["blurb"].toString());
        this->champion_data[json[key].toObject()["key"].toString().toInt()].set_resource_type(json[key].toObject()["partype"].toString());

        if(champion_data_needs_update){
            values += QString("(%1, '%2', '%3'),")
                          .arg(this->champion_data[json[key].toObject()["key"].toInt()].get_id())
                          .arg(this->champion_data[json[key].toObject()["key"].toInt()].get_name(),
                               this->champion_data[json[key].toObject()["key"].toInt()].get_image_url());
        }
    }
    if(champion_data_needs_update){
        values += QString("(-1, 'N/A', 'N/A')");
        //values.chop(1);     // get rid of the final comma from the query
        database->update_champion_data(values);
    }
}

/**
 * @brief Set the summoner spell data.
 * @param json - json object with the data key
 * @param database - database pointer that will handle any queries and transactions
 */
void StaticData::set_summoner_spell_data(QJsonObject json, PostgresDatabase* database){
    bool summoner_spell_needs_update = database != nullptr && json.keys().length() != database->get_num_summoner_spells_database();
    if(summoner_spell_needs_update){
        cout << "Outdated summoner spell data detected.  Cleansing old summoner spell data from the database..." << endl;
        database->delete_summoner_spells();
    }

    QString values;
    foreach(QString key, json.keys()){
        this->summoner_spell_data[json[key].toObject()["key"].toString().toInt()]["summonerSpellName"] = json[key].toObject()["name"].toString().toStdString();
        this->summoner_spell_data[json[key].toObject()["key"].toString().toInt()]["summonerSpellDescription"] = json[key].toObject()["description"].toString().toStdString();

        if(summoner_spell_needs_update){
            values += QString("(%1, '%2', '%3'),")
                          .arg(json[key].toObject()["key"].toString().toInt())
                          .arg(QString::fromStdString(this->summoner_spell_data[json[key].toObject()["key"].toString().toInt()]["summonerSpellName"]),
                               QString::fromStdString(regex_replace(this->summoner_spell_data[json[key].toObject()["key"].toString().toInt()]["summonerSpellDescription"], regex("'"), "''")));
        }
    }
    if(summoner_spell_needs_update){
        values.chop(1);
        database->update_summoner_spell_data(values);
    }
}

/**
 * @brief Set the queue data
 * @param json - simple json array containing the queueId, map, description, and notes.
 * The most relevant queueIds will have no notes
 */
void StaticData::set_queue_data(QJsonArray json, PostgresDatabase* database){
    int queue_length = 0;
    QString values;
    for(int i = 0; i < json.size(); i++){
        // If there are no notes, then add the queue to the static data
        /*QJsonObject json_object = json[i].toObject();
        QJsonDocument json_output;
        json_output.setObject(json_object);
        cout << json_output.toJson(QJsonDocument::Indented).toStdString() << endl;*/
        if(json[i].toObject()["notes"].toString().toStdString() == "" || json[i].toObject()["notes"].isNull()){
            this->queue_data[json[i].toObject()["queueId"].toInt()]["queueMap"] = json[i].toObject()["map"].toString().toStdString();
            this->queue_data[json[i].toObject()["queueId"].toInt()]["queueDescription"] = json[i].toObject()["description"].toString().toStdString();

            queue_length++;
            values += QString("(%1, '%2', '%3'),")
                          .arg(json[i].toObject()["queueId"].toInt())
                          .arg(QString::fromStdString(regex_replace(this->queue_data[json[i].toObject()["queueId"].toInt()]["queueMap"], regex("'"), "''")),
                               QString::fromStdString(regex_replace(this->queue_data[json[i].toObject()["queueId"].toInt()]["queueDescription"], regex("'"), "''")));
        }
    }

    bool queue_needs_update = database != nullptr && queue_length != database->get_num_queues_database();
    if(queue_needs_update){
        cout << "Outdated queue data detected.  Clearing queue data from the database..." << endl;
        database->delete_queues();
        values.chop(1);
        database->update_queue_data(values);
    }
    // DEBUG: print out the queue data
    /*
    for(auto const &outer: this->queue_data){
        for(auto const &inner: outer.second)
            cout << inner.first << ": " << inner.second << endl;
        cout << endl;
    }*/
}

/**
 * @brief Set the queue data
 * @param json - simple json array containing the mapId, mapName, and notes
 */
void StaticData::set_map_data(QJsonArray json, PostgresDatabase* database){
    bool map_needs_update = database != nullptr && json.size() != database->get_num_maps_database();
    if(map_needs_update){
        cout << "Outdated map data detected.  Clearing old map data from the database..." << endl;
        database->delete_maps();
    }

    QString values;
    for(int i = 0; i < json.size(); i++){
        this->map_data[json[i].toObject()["mapId"].toInt()]["mapName"] = json[i].toObject()["mapName"].toString().toStdString();

        if(map_needs_update){
            values += QString("(%1, '%2'),")
                          .arg(json[i].toObject()["mapId"].toInt())
                          .arg(QString::fromStdString(regex_replace(this->map_data[json[i].toObject()["mapId"].toInt()]["mapName"], regex("'"), "''")));
        }
    }

    if(map_needs_update){
        values.chop(1);
        database->update_map_data(values);
    }
    // DEBUG: print out the map data
    /*
    for(auto const &outer: this->map_data){
        for(auto const &inner: outer.second)
            cout << inner.first << ": " << inner.second << endl;
        cout << endl;
    }
    */
}

/**
 * @brief Set the item data.  Will only choose items that have any one of the following attributes:
 * it's in store, it's purchasable, it's a trinket, it's an ornn item, or it's from summoner's rift/aram
 * @param json - json object with the data key
 */
void StaticData::set_item_data(QJsonObject json, PostgresDatabase* database){
    int item_length = 0;
    QString values;
    foreach(QString key, json.keys()){
        if(json[key].toObject()["gold"].toObject()["purchasable"].toBool()
            || json[key].toObject()["maps"].toObject()["11"].toBool()
                || json[key].toObject()["maps"].toObject()["12"].toBool()
                    || json[key].toObject()["description"].toString().toStdString().find("ornn") != string::npos
                        || json[key].toObject()["tags"].toArray().contains("Trinket")){

            if(key.toInt() < 3901 || key.toInt() > 3903)
                this->item_data[key.toInt()]["itemName"] = json[key].toObject()["name"].toString().toStdString();
            else
                this->item_data[key.toInt()]["itemName"] = regex_replace(json[key].toObject()["name"].toString().toStdString(), regex("(<.+?>)+"), " ");
            this->item_data[key.toInt()]["itemGold"] = to_string(json[key].toObject()["gold"].toObject()["total"].toInt());
            this->item_data[key.toInt()]["itemDescription"] = regex_replace(json[key].toObject()["description"].toString().toStdString(), regex("(<.+?>)+"), " ");

            if(this->item_data[key.toInt()]["itemDescription"] != ""){
                values += QString("(%1, '%2'")
                              .arg(key.toInt())
                              .arg(QString::fromStdString(regex_replace(this->item_data[key.toInt()]["itemName"], regex("'"), "''")));
                values += QString(", %1, '%2', '%3'),")
                              .arg(stoi(this->item_data[key.toInt()]["itemGold"]))
                              .arg(QString::fromStdString(regex_replace(this->item_data[key.toInt()]["itemDescription"], regex("'"), "''")),
                                   QString::fromStdString("https://ddragon.leagueoflegends.com/cdn/"+ this->get_version() +"/img/item/"+ key.toStdString() +".png"));
                item_length++;
            }
        }
    }
    bool item_needs_update = database != nullptr && item_length != database->get_num_items_database();
    if(item_needs_update){
        cout << "Outdated item data detected.  Clearing item data from the database..." << endl;
        database->delete_items();
        values.chop(1);
        database->update_item_data(values);
    }
}
