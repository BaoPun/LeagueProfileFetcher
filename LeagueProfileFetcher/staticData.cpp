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
 * @brief Getter to retrieve the champion's name given the numerical key
 * @param the numerical key
 * @return the champion name from the champion_data mapping.
 */
string StaticData::get_champion_name_by_key(int key){
    return this->champion_data[key]["championName"];
}

/**
 * @brief Getter to retrieve the champion's immage url given the numerical key
 * @param the numerical key
 * @return the champion's image url from the champion_data mapping.
 */
string StaticData::get_champion_url_by_key(int key){
    return this->champion_data[key]["championImage"];
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
void StaticData::set_version(string version){
    this->version = version;
}

/**
 * @brief Set the champion data.
 * @param json - json object with the data key
 */
void StaticData::set_champion_data(QJsonObject json){
    foreach(QString key, json.keys()){
        // For some reason, RIOT uses Wukong's name as MonkeyKing in their API.
        // Properly change the Wukong, but the URL for the image MUST remain as MonkeyKing
        if(key.toStdString() == "MonkeyKing")
            this->champion_data[json[key].toObject()["key"].toString().toInt()]["championName"] = "Wukong";
        else
            this->champion_data[json[key].toObject()["key"].toString().toInt()]["championName"] = key.toStdString();
        this->champion_data[json[key].toObject()["key"].toString().toInt()]["championImage"] = "http://ddragon.leagueoflegends.com/cdn/" + this->version + "/img/champion/" + key.toStdString() + ".png";

        // DEBUG: print out the champion name and image url to the console
        //cout << "Champion name: " << this->champion_data[json[key].toObject()["key"].toString().toInt()]["championName"] << endl;
        //cout << "Champion image url: " << this->champion_data[json[key].toObject()["key"].toString().toInt()]["championImage"] << endl << endl;
    }
    //cout << "Champion data size: " << this->champion_data.size() << endl;
}

/**
 * @brief Set the summoner spell data.
 * @param json - json object with the data key
 */
void StaticData::set_summoner_spell_data(QJsonObject json){
    foreach(QString key, json.keys()){
        this->summoner_spell_data[json[key].toObject()["key"].toString().toInt()]["summonerSpellName"] = json[key].toObject()["name"].toString().toStdString();
        this->summoner_spell_data[json[key].toObject()["key"].toString().toInt()]["summonerSpellDescription"] = json[key].toObject()["description"].toString().toStdString();

        // DEBUG: print out the summoner spell name and description to the console
        //cout << "Summoner spell name: " << this->summoner_spell_data[json[key].toObject()["key"].toString().toInt()]["summonerSpellName"] << endl;
        //cout << "Summoner spell description: " << this->summoner_spell_data[json[key].toObject()["key"].toString().toInt()]["summonerSpellDescription"] << endl << endl;
    }/*
    for(auto const &outer: this->summoner_spell_data){
        for(auto const &inner: outer.second)
            cout << inner.first << ": " << inner.second << endl;
        cout << endl;
    }*/
    //cout << "Summoner spell data size: " << this->summoner_spell_data.size() << endl;
}

/**
 * @brief Set the queue data
 * @param json - simple json array containing the queueId, map, description, and notes.
 * The most relevant queueIds will have no notes
 */
void StaticData::set_queue_data(QJsonArray json){
    for(int i = 0; i < json.size(); i++){
        // If there are no notes, then add the queue to the static data
        /*QJsonObject json_object = json[i].toObject();
        QJsonDocument json_output;
        json_output.setObject(json_object);
        cout << json_output.toJson(QJsonDocument::Indented).toStdString() << endl;*/
        if(json[i].toObject()["notes"].toString().toStdString() == "" || json[i].toObject()["notes"].isNull()){
            this->queue_data[json[i].toObject()["queueId"].toInt()]["queueMap"] = json[i].toObject()["map"].toString().toStdString();
            this->queue_data[json[i].toObject()["queueId"].toInt()]["queueDescription"] = json[i].toObject()["description"].toString().toStdString();
            //cout << "nice id: " << json[i].toObject()["queueId"].toInt() << endl;
            //cout << "nice map: " << json[i].toObject()["map"].toString().toStdString() << endl;
            //cout << "nice description: " << json[i].toObject()["description"].toString().toStdString() << endl;
        }
    }

    // DEBUG: print out the queue data
    /*
    for(auto const &outer: this->queue_data){
        for(auto const &inner: outer.second)
            cout << inner.first << ": " << inner.second << endl;
        cout << endl;
    }*/
    //cout << "Queue data size: " << this->queue_data.size() << endl;
}

/**
 * @brief Set the queue data
 * @param json - simple json array containing the mapId, mapName, and notes
 */
void StaticData::set_map_data(QJsonArray json){
    for(int i = 0; i < json.size(); i++)
        this->map_data[json[i].toObject()["mapId"].toInt()]["mapName"] = json[i].toObject()["mapName"].toString().toStdString();

    // DEBUG: print out the map data
    /*
    for(auto const &outer: this->map_data){
        for(auto const &inner: outer.second)
            cout << inner.first << ": " << inner.second << endl;
        cout << endl;
    }
    */
    //cout << "Map data size: " << this->map_data.size() << endl;
}

/**
 * @brief Set the item data.  Will only choose items that have any one of the following attributes:
 * it's in store, it's purchasable, it's a trinket, it's an ornn item, or it's from summoner's rift/aram
 * @param json - json object with the data key
 */
void StaticData::set_item_data(QJsonObject json){
    foreach(QString key, json.keys()){
        if(json[key].toObject()["gold"].toObject()["purchasable"].toBool()
            || json[key].toObject()["maps"].toObject()["11"].toBool()
                || json[key].toObject()["maps"].toObject()["12"].toBool()
                    || json[key].toObject()["description"].toString().toStdString().find("ornn") != string::npos
                        || json[key].toObject()["tags"].toArray().contains("Trinket")){
            this->item_data[key.toInt()]["itemName"] = json[key].toObject()["name"].toString().toStdString();
            this->item_data[key.toInt()]["itemGold"] = to_string(json[key].toObject()["gold"].toObject()["total"].toString().toInt());
            this->item_data[key.toInt()]["itemDescription"] = json[key].toObject()["plaintext"].toString().toStdString();
        }
    }
    //cout << "Item data size: " << this->item_data.size() << endl;
}
