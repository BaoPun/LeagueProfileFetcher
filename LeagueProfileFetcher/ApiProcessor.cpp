#include "./ApiProcessor.h"


/**
 * @brief Constructor of the ApiProcessor class.  Instantiates the parent to the network manager.
 * @param parent
 */
ApiProcessor::ApiProcessor(QObject *parent){
    // Set up the connections.  Let the manager reference "this" window, and have the request and reply be null initially
    this->net_manager = new QNetworkAccessManager(parent);
    this->net_reply = nullptr;
    this->data_buffer.clear();

    // Set the flag to be false
    this->has_entered_new_summoner = false;
}

/**
 * @brief Destructor for the api processor.
 */
ApiProcessor::~ApiProcessor(){
    // Delete the network reply before deleting the access manager.
    // Otherwise, this will crash the program upon closing.
    if(this->net_reply != nullptr){
        delete this->net_reply;
        cout << "Deleted the network reply" << endl;
    }
    if(this->net_manager != nullptr){
        delete this->net_manager;
        cout << "Deleted the network access manager" << endl;
    }
}

/**
 * @brief Run the main window.  Also run a signal to detect when the window is closed.
 */
void ApiProcessor::execute_main_window(){
    // Process the version
    this->process_api_data("https://ddragon.leagueoflegends.com/api/versions.json", 1);

    // Show the main window
    this->main_window.execute();

    // Create a connection to the main window when it is destroyed; open the secondary window in this case
    connect(&this->main_window, SIGNAL(windowClose()), this, SLOT(open_secondary_window()));
}


/**
 * @brief Run the api data and then open the second window
 */
void ApiProcessor::open_secondary_window(){
    if(!this->has_entered_new_summoner){
        this->process_api_data(this->main_window.generate_summoner_api_url(), 7);
        this->has_entered_new_summoner = true;
        this->summoner_data.set_platform(this->main_window.get_platform());
        this->summoner_data.set_region(this->main_window.get_region());
    }
    else{
        this->process_api_data(this->summoner_profile_window.generate_summoner_api_url(), 7);
        this->summoner_data.set_platform(this->summoner_profile_window.get_platform());
        this->summoner_data.set_region(this->summoner_profile_window.get_region());
    }

    this->summoner_profile_window.execute();

    // Create a connection to the secondary window when it is hidden; again, open the secondary window
    // Because this slot is recursively calling the same slot, the 5th argument guarantees a unique connection
    connect(&this->summoner_profile_window, SIGNAL(windowHide()), this, SLOT(open_secondary_window()), Qt::UniqueConnection);
}


/**
 * @brief Set up the connection to the given URL.
 * @param url
 */
void ApiProcessor::process_api_data(QString url, int json_index){
    //cout << "URL to process: " << url.toStdString() << endl;

    // Set up the url connection and create the signal + trigger
    QNetworkRequest request{
        QUrl(url)
    };
    this->net_reply = this->net_manager->get(request);

    // Connections to read the data into the data buffer and to retrieve the data from the data buffer
    // For retrieving data, since it takes in arguments, we have to use a lambda function instead of &
    connect(this->net_reply, &QNetworkReply::readyRead, this, &ApiProcessor::read_data);
    connect(this->net_reply, &QNetworkReply::finished, this, [=]{ retrieve_data(json_index); });
}

/**
 * @brief Set up the connection to multiple urls.  A QEventLoop is used to ensure that ALL urls are processed.
 * @param url_list - the list of urls in a vector
 */
void ApiProcessor::process_multiple_api_data(vector<QString> url_list, int offset){
    for(int i = 0; i < url_list.size(); i++){
        QNetworkRequest request;
        request.setUrl(url_list[i]);
        this->net_reply = this->net_manager->get(request);

        // With an event loop, it forces the current api call to complete before the next one.
        QEventLoop event_loop;
        connect(this->net_reply, &QNetworkReply::readyRead, this, &ApiProcessor::read_data);
        connect(this->net_reply, &QNetworkReply::finished, this, [=]{ retrieve_data(i + 2 + offset); });
        connect(this->net_reply, &QNetworkReply::finished, &event_loop, &QEventLoop::quit);
        event_loop.exec();
    }
}


/**
 * @brief Read in the data from the request and append it to the data buffer.
 */
void ApiProcessor::read_data(){
    this->data_buffer.append(this->net_reply->readAll());
}

/**
 * @brief Process the data from the data buffer.
 * If there was an error with the data itself, then stop.
 * Otherwise, create a new JSON object to store this data.
 */
void ApiProcessor::retrieve_data(int index){
    // If there was an error, print the error to the console and immediately escape this function
    if(this->net_reply->error() != QNetworkReply::NoError){
        cout << "Error description: " << this->net_reply->errorString().toStdString() << endl;
        if(index == 11)
            cout << "Main error is that the summoner is currently NOT in a live game" << endl << endl;
        else{
            this->summoner_profile_window.set_summoner_placeholder_label_text("INVALID USER");

            // Reset all data
            this->summoner_data.reset_all_rank_data();
            this->summoner_profile_window.set_summoner_solo_rank_label_text(this->summoner_data.get_solo_queue_data().get_rank());
            this->summoner_profile_window.set_summoner_flex_rank_label_text(this->summoner_data.get_flex_queue_data().get_rank());

        }

        // At the end of the data processing, clear out the data buffer
        this->data_buffer.clear();

        return;
    }

    // The data is either static or dynamic.
    // Indexes 1-6 are static
    // Set up the version.
    if(index == 1){
        // Grab the latest version (the first index from the json array), set it, and then clear the buffer
        QJsonArray json_array = QJsonDocument::fromJson(this->data_buffer).array();
        cout << "Latest version: " + json_array[0].toString().toStdString() << endl;
        this->static_data.set_version(json_array[0].toString().toStdString());
        this->data_buffer.clear();

        // Add the urls to a locally defined vector
        vector<QString> url_list;
        url_list.push_back(QString::fromStdString("http://ddragon.leagueoflegends.com/cdn/" + this->static_data.get_version() + "/data/en_US/champion.json"));
        url_list.push_back(QString::fromStdString("http://ddragon.leagueoflegends.com/cdn/" + this->static_data.get_version() + "/data/en_US/summoner.json"));
        url_list.push_back("https://static.developer.riotgames.com/docs/lol/queues.json");
        url_list.push_back("https://static.developer.riotgames.com/docs/lol/maps.json");
        url_list.push_back(QString::fromStdString("http://ddragon.leagueoflegends.com/cdn/" + this->static_data.get_version() + "/data/en_US/item.json"));

        // Process all of the urls that were added
        this->process_multiple_api_data(url_list);
    }
    // Set up the champion data
    else if(index == 2)
        this->static_data.set_champion_data(QJsonDocument::fromJson(this->data_buffer).object()["data"].toObject());
    // Set up the summoner spell data
    else if(index == 3)
        this->static_data.set_summoner_spell_data(QJsonDocument::fromJson(this->data_buffer).object()["data"].toObject());
    // Set up the queue data
    else if(index == 4)
        this->static_data.set_queue_data(QJsonDocument::fromJson(this->data_buffer).array());
    // Set up the map data
    else if(index == 5)
        this->static_data.set_map_data(QJsonDocument::fromJson(this->data_buffer).array());
    // Set up the item data
    else if(index == 6)
        this->static_data.set_item_data(QJsonDocument::fromJson(this->data_buffer).object()["data"].toObject());
    // Set up the summoner api data
    else if(index == 7){
        this->summoner_data.process_summoner_data(QJsonDocument::fromJson(this->data_buffer).object());
        this->summoner_profile_window.set_summoner_placeholder_label_text(summoner_data.get_summoner_name());
        this->data_buffer.clear();

        // The summoner data was valid: process the rank, champion mastery, match history, and live game data
        vector<QString> url_list;
        url_list.push_back("https://" + this->summoner_data.get_platform() + ".api.riotgames.com/lol/league/v4/entries/by-summoner/" + this->summoner_data.get_encrypted_summoner_id() + "/?api_key=" + QString::fromStdString(API_KEY));
        url_list.push_back("https://" + this->summoner_data.get_platform() + ".api.riotgames.com/lol/champion-mastery/v4/champion-masteries/by-summoner/" + this->summoner_data.get_encrypted_summoner_id() + "/top?count=7&api_key=" + QString::fromStdString(API_KEY));
        url_list.push_back("https://" + this->summoner_data.get_region() + ".api.riotgames.com/lol/match/v5/matches/by-puuid/" + this->summoner_data.get_summoner_puuid() + "/ids?start=0&count=7&api_key=" + QString::fromStdString(API_KEY));
        url_list.push_back("https://" + this->summoner_data.get_platform() + ".api.riotgames.com/lol/spectator/v4/active-games/by-summoner/" + this->summoner_data.get_encrypted_summoner_id() + "?api_key=" + QString::fromStdString(API_KEY));

        // Process all of the urls that were added
        this->process_multiple_api_data(url_list, 6);
    }
    // Set up the summoner rank data
    else if(index == 8){
        this->summoner_data.process_rank_data(QJsonDocument::fromJson(this->data_buffer).array());
        this->summoner_profile_window.set_summoner_solo_rank_label_text(this->summoner_data.get_solo_queue_data().get_rank() + "\n" + QString::fromStdString(to_string(this->summoner_data.get_solo_queue_data().get_wins())) + " wins, " + QString::fromStdString(to_string(this->summoner_data.get_solo_queue_data().get_losses())) + " losses\n" + QString::fromStdString(to_string(this->summoner_data.get_solo_queue_data().get_league_points())) + " LP");
        this->summoner_profile_window.set_summoner_flex_rank_label_text(this->summoner_data.get_flex_queue_data().get_rank() + "\n" + QString::fromStdString(to_string(this->summoner_data.get_flex_queue_data().get_wins())) + " wins, " + QString::fromStdString(to_string(this->summoner_data.get_flex_queue_data().get_losses())) + " losses\n" + QString::fromStdString(to_string(this->summoner_data.get_flex_queue_data().get_league_points())) + " LP");
    }
    // Set up the summoner's champion mastery data
    else if(index == 9){
        cout << "NICE mastery data" << endl;
    }
    // Set up the summoner's match history data
    else if(index == 10){
        cout << "NICE match history data" << endl;
    }
    // Set up the summoner's live game data
    else if(index == 11){
        cout << "NICE live game data" << endl;
    }
    // Set up each summoner's match data
    else if(index == 12){
        cout << "NICE match data" << endl;
    }

    // At the end of the data processing, clear out the data buffer
    if(!this->data_buffer.isEmpty())
        this->data_buffer.clear();
}

/**
 * @brief Getter to the network access manager
 * @return the network access manager (QNetworkAccessManager *)
 */
QNetworkAccessManager *ApiProcessor::get_network_access_manager(){
    return this->net_manager;
}

/**
 * @brief Getter to the network reply
 * @return the network reply (QNetworkReply *)
 */
QNetworkReply *ApiProcessor::get_network_reply(){
    return this->net_reply;
}

/**
 * @brief Getter to the summoner data
 * @return the summoner data (SummonerData)
 */
SummonerData ApiProcessor::get_summoner_data(){
    return this->summoner_data;
}

/**
 * @brief Setter to the network access manager
 * @param net_manager - the new network access manager to update the processor object
 */
void ApiProcessor::set_network_access_manager(QNetworkAccessManager *net_manager){
    this->net_manager = net_manager;
}

/**
 * @brief Setter to the network reply
 * @param net_reply - the new network reply to update the processor object
 */
void ApiProcessor::set_network_reply(QNetworkReply *net_reply){
    this->net_reply = net_reply;
}
