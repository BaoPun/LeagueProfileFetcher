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

    // Make a connection to the Postgres SQL database
    this->database = new PostgresDatabase();
    if(!this->database->is_database_connected()){
        cout << "FAILED..." << endl;
        delete this->database;
        this->database = nullptr;
    }
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

    // Close the database connection, if not already closed
    if(this->database != nullptr)
        delete this->database;
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
    // If the signal came from the champion window, then show the summoner window and ACK the signal.
    if(this->champion_window.is_signal_triggered()){
        this->champion_window.acknowledged_signal();
        this->summoner_profile_window.execute();
        return;
    }
    // If the signal came from the main window, then automatically make the flag true.
    if(this->main_window.get_main_signal())
        this->has_entered_new_summoner = true;
    else
        this->has_entered_new_summoner = this->summoner_data.get_summoner_name().toLower() != this->summoner_profile_window.get_summoner().toLower()
                                         || this->summoner_data.get_platform() != this->summoner_profile_window.get_platform()
                                         || this->summoner_data.get_tagline().toLower() != this->summoner_profile_window.get_tagline().toLower();

    // If new information was entered, then process it and make a new window.
    // Otherwise, don't make a new window.
    if(this->has_entered_new_summoner){
        // Set the summoner name, the region, and the tagline, which is required for the riot id url.
        if(this->main_window.get_main_signal()){
            this->summoner_data.set_summoner_name(this->main_window.get_summoner());
            this->summoner_data.set_region(this->main_window.get_region());
            if(this->main_window.get_tagline() == "")
                this->summoner_data.set_tagline(this->summoner_data.get_region());
            else
                this->summoner_data.set_tagline(this->main_window.get_tagline());

            // Set the platform as well for good measure
            this->summoner_data.set_platform(this->main_window.get_platform());

            // Finally, trigger the main signal so that future calls to this signal
            // will only look at the second window
            this->main_window.trigger_signal();
        }
        else{
            this->summoner_data.set_summoner_name(this->summoner_profile_window.get_summoner());
            this->summoner_data.set_region(this->summoner_profile_window.get_region());
            if(this->summoner_profile_window.get_tagline() == "")
                this->summoner_data.set_tagline(this->summoner_data.get_region());
            else
                this->summoner_data.set_tagline(this->summoner_profile_window.get_tagline());

            // Set the platform as well for good measure
            this->summoner_data.set_platform(this->summoner_profile_window.get_platform());
        }
        // After the initial sets, generate the riot id url and then process the api.
        this->process_api_data(this->summoner_data.generate_riot_id_url(), 7);

        // Execute the secondary window
        this->summoner_profile_window.execute();

        // Create a connection to the secondary window when it is hidden; again, open the secondary window
        // Because this slot is recursively calling the same slot, the 5th argument guarantees a unique connection
        // So that we can search for different users
        connect(&this->summoner_profile_window, SIGNAL(windowHide()), this, SLOT(open_secondary_window()), Qt::UniqueConnection);
        connect(&this->summoner_profile_window, SIGNAL(open_champion_window_signal(QString)), this, SLOT(open_champion_window(QString)), Qt::UniqueConnection);
    }
    // Otherwise, same information was used. Display message box and retain the secondary window
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Same information detected.");
        msgBox.setText("You have entered the same user.  Nothing will change.");
        msgBox.exec();
        this->summoner_profile_window.show();
    }

}

/**
 * @brief From open_secondary_window, this is called when a champion is clicked on.
 * This function will hide the secondary window and show a new window
 * that will contain the abilities of the champion.
 * @param champion_name - the name of the champion passed in.
 */
void ApiProcessor::open_champion_window(QString champion_name){
    // Hide the summoner window
    this->summoner_profile_window.hide();

    // Process the champion specific info (already done as static data)
    this->champion_window.set_champion_name(champion_name);

    // And show the champion window
    this->champion_window.execute();

    // Also run a connection from champion window to here to redisplay the summoner window.
    connect(&this->champion_window, SIGNAL(show_summoner_window_signal()), this, SLOT(open_secondary_window()), Qt::UniqueConnection);
}


/**
 * @brief Set up the connection to the given URL.
 * @param url
 */
void ApiProcessor::process_api_data(QString url, int json_index){
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
        QNetworkRequest request{
            QUrl(url_list[i])
        };
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
 * @brief Set up multiple images called from the web.
 * Used for mastery data, where we retrieve a list of images from the database,
 * and then we use an Event Loop to retrieve each image from the web.
 * We then pass in the image object to the summoner profile window for display.
 */
void ApiProcessor::process_multiple_image_data(){
    // First, clear the data buffer if not already cleared out.
    if(!this->data_buffer.isEmpty())
        this->data_buffer.clear();

    if(this->database != nullptr){
        // First, get the list of all mastered champions by the searched user
        vector<SummonerMastery> mastered_champions = this->summoner_data.get_all_mastery_champions();

        // Continue if there is at least 1 result
        // Otherwise, just delete the previous summoner's list of mastered champions' images.
        if(!mastered_champions.empty()){
            // Second, organize the list of champions for use in the database
            QString values;
            for(int i = 0; i < mastered_champions.size(); i++){
                values += ("(" + QString::fromStdString(to_string(i+1)) + ", " + QString::fromStdString(to_string(mastered_champions[i].get_champion_id())) + ")");
                if(i != mastered_champions.size() - 1)
                    values += ", ";
            }

            // Third, run the query to get the list of image urls
            vector<QString> image_urls = this->database->get_champion_image_urls_from_ids(values);


            // Fourth, create an event loop to process all images and store them into another vector
            vector<QImage> images;
            for(int i = 0; i < image_urls.size(); i++){
                QNetworkRequest request{
                    QUrl(image_urls[i])
                };
                this->net_reply = this->net_manager->get(request);

                QEventLoop event_loop;
                connect(this->net_reply, &QNetworkReply::readyRead, this, &ApiProcessor::read_data);
                connect(this->net_reply, &QNetworkReply::finished, this, [&images, this]{ add_image_from_api(images); });
                connect(this->net_reply, &QNetworkReply::finished, &event_loop, &QEventLoop::quit);
                event_loop.exec();
            }

            // Finally, send the images to the summoner profile
            this->summoner_profile_window.set_summoner_champion_mastery_images(images, mastered_champions);
        }
        else
            this->summoner_profile_window.delete_summoner_mastered_champions_images();
    }
    else
        cout << "No database connection established.  No champion image will be displayed." << endl;
}

/**
 * @brief Add the processed image to the vector
 */
void ApiProcessor::add_image_from_api(vector<QImage>& image_urls){
    // First, check if there was an error.
    //cout << this->data_buffer.toStdString() << endl;
    if(this->net_reply->error() != QNetworkReply::NoError){
        cout << "There was something wrong with the image processing..." << endl;
    }
    else{
        // Add the image by loading the image from the data buffer
        QImage new_image;
        new_image.loadFromData(this->data_buffer);
        if(!new_image.isNull()){
            new_image = new_image.scaled(80, 80, Qt::KeepAspectRatio, Qt::FastTransformation);
            image_urls.push_back(new_image);
        }
        else
            cout << "NICE TRY" << endl << endl;
    }

    // At the end of the data processing, clear out the data buffer
    if(!this->data_buffer.isEmpty())
        this->data_buffer.clear();
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
        if(index == 12)
            cout << "Main error is that the summoner is currently NOT in a live game" << endl << endl;
        else{
            this->summoner_profile_window.set_summoner_placeholder_label_text("INVALID USER");

            // Reset all data
            this->summoner_data.reset_all_rank_data();
            this->summoner_profile_window.delete_summoner_emblems();
            this->summoner_profile_window.delete_summoner_mastered_champions_images();
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
        this->static_data.set_version(json_array[0].toString().toStdString(), this->database);
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
        this->static_data.set_champion_data(QJsonDocument::fromJson(this->data_buffer).object()["data"].toObject(), this->database);
    // Set up the summoner spell data
    else if(index == 3)
        this->static_data.set_summoner_spell_data(QJsonDocument::fromJson(this->data_buffer).object()["data"].toObject(), this->database);
    // Set up the queue data
    else if(index == 4)
        this->static_data.set_queue_data(QJsonDocument::fromJson(this->data_buffer).array(), this->database);
    // Set up the map data
    else if(index == 5)
        this->static_data.set_map_data(QJsonDocument::fromJson(this->data_buffer).array(), this->database);
    // Set up the item data
    else if(index == 6)
        this->static_data.set_item_data(QJsonDocument::fromJson(this->data_buffer).object()["data"].toObject(), this->database);
    // Set up the riot id data (puuid, summoner name, tagline)
    else if(index == 7){
        this->summoner_data.process_riot_data(QJsonDocument::fromJson(this->data_buffer).object());
        this->data_buffer.clear();

        // Immediately after processing the riot data, process the summoner api url
        this->process_api_data(this->summoner_data.generate_summoner_api_url(), 8);
    }
    // Set up the summoner api data
    else if(index == 8){
        this->summoner_data.process_summoner_data(QJsonDocument::fromJson(this->data_buffer).object());
        this->data_buffer.clear();

        this->summoner_profile_window.set_summoner_placeholder_label_text(this->summoner_data.get_summoner_name() + "#" + this->summoner_data.get_tagline());

        // The summoner data was valid: process the rank, champion mastery, match history, and live game data
        vector<QString> url_list;
        url_list.push_back("https://" + this->summoner_data.get_platform() + ".api.riotgames.com/lol/league/v4/entries/by-summoner/" + this->summoner_data.get_encrypted_summoner_id() + "/?api_key=" + QString::fromStdString(API_KEY));
        url_list.push_back("https://" + this->summoner_data.get_platform() + ".api.riotgames.com/lol/champion-mastery/v4/champion-masteries/by-puuid/" + this->summoner_data.get_summoner_puuid() + "/top?count=10&api_key=" + QString::fromStdString(API_KEY));
        //url_list.push_back("https://" + this->summoner_data.get_platform() + ".api.riotgames.com/lol/champion-mastery/v4/champion-masteries/by-summoner/" + this->summoner_data.get_encrypted_summoner_id() + "?api_key=" + QString::fromStdString(API_KEY));
        url_list.push_back("https://" + this->summoner_data.get_region() + ".api.riotgames.com/lol/match/v5/matches/by-puuid/" + this->summoner_data.get_summoner_puuid() + "/ids?start=0&count=7&api_key=" + QString::fromStdString(API_KEY));
        url_list.push_back("https://" + this->summoner_data.get_platform() + ".api.riotgames.com/lol/spectator/v4/active-games/by-summoner/" + this->summoner_data.get_encrypted_summoner_id() + "?api_key=" + QString::fromStdString(API_KEY));

        // Process all of the urls that were added
        this->process_multiple_api_data(url_list, 7);
    }
    // Set up the summoner rank data
    else if(index == 9){
        this->summoner_data.process_rank_data(QJsonDocument::fromJson(this->data_buffer).array());
        SummonerRank solo_queue_data = this->summoner_data.get_solo_queue_data();
        SummonerRank flex_queue_data = this->summoner_data.get_flex_queue_data();

        // In addition, load the summoner rank image
        this->summoner_profile_window.set_summoner_rank_emblems(solo_queue_data, flex_queue_data);
    }
    // Set up the summoner's champion mastery data
    else if(index == 10){
        this->summoner_data.process_mastery_data(QJsonDocument::fromJson(this->data_buffer).array(), this->database, this->static_data);
        this->process_multiple_image_data();
    }
    // Set up the summoner's match history data
    else if(index == 11){
        cout << "NICE match history data" << endl;
    }
    // Set up the summoner's live game data
    else if(index == 12){
        cout << "NICE live game data" << endl;
    }
    // Set up each summoner's match data
    else if(index == 13){
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
