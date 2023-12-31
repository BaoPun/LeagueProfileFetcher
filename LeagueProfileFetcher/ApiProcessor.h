#ifndef APIPROCESSOR_H
#define APIPROCESSOR_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QByteArray>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QImageReader>

#include "./mainwindow.h"
#include "./summonerwindow.h"
#include "./championWindow.h"
#include "./summonerData.h"
#include "./staticData.h"
#include "./databaseInfo.h"

class ApiProcessor : public QObject{
    private:
        Q_OBJECT
        // Network methods for API calls
        QNetworkAccessManager *net_manager;
        QNetworkReply *net_reply;
        QByteArray data_buffer;

        // Database
        PostgresDatabase* database;

        // Store the windows
        MainWindow main_window;
        SummonerProfile summoner_profile_window;
        ChampionWindow champion_window;


        // Store league-related information from the user
        SummonerData summoner_data;

        // Did our api call to get summoner process successfully?
        bool is_summoner_lookup_successful;



        // Store async'ed data
        //vector<QFutureWatcher<void>> async_api_future_list;

        // Store the JSON object
        /*
            Version will be 1
            Champion data will be 2
            Summoner spell will be 3
            Queues will be 4
            Maps will be 5
            Items will be 6
            Summoner data will be 7
            Summoner rank data will be 8
            Summoner mastery data will be 9
            Summoner match history data will be 10
            Each of the summoner's matches from match history will be 11
            Summoner live game data will be 12
        */
        // Store the static data (1-6)
        StaticData static_data;

        // Boolean to determine if the main window was closed upon entering a new summoner
        bool has_entered_new_summoner;

    private slots:
        void read_data();
        void retrieve_data(int);
        void open_secondary_window();
        void add_image_from_api(vector<QImage>&);
        void open_champion_window(int);

    public:
        explicit ApiProcessor(QObject * = nullptr);
        ~ApiProcessor();

        // Run the main window
        void execute_main_window();

        // Process api data
        void process_api_data(QString, int);
        void process_multiple_api_data(vector<QString>, int = 0);
        void process_multiple_image_data();

        // Close database
        void close_database_connection();


        // Getters
        QNetworkAccessManager *get_network_access_manager();
        QNetworkReply *get_network_reply();
        SummonerData get_summoner_data();
        bool get_summoner_lookup_status();

        // Setters
        void set_network_access_manager(QNetworkAccessManager *);
        void set_network_reply(QNetworkReply *);
};


#endif // APIPROCESSOR_H
