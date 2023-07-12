#ifndef SUMMONERDATA_H
#define SUMMONERDATA_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QString>

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class SummonerData{
    private:
        QString summoner_name;
        QString encrypted_summoner_id;
        QString summoner_puuid;
        QString platform, region;
        int summoner_level;
        bool is_data_valid;

    public:
        SummonerData();

        // Data Processing
        void process_summoner_data(QJsonObject);
        void process_rank_data(QJsonArray);

        // Getters
        QString get_summoner_name();
        QString get_encrypted_summoner_id();
        QString get_summoner_puuid();
        int get_summoner_level();
        bool get_is_data_valid();
        QString get_platform();
        QString get_region();

        // Setters
        void set_summoner_name(QString);
        void set_encrypted_summoner_id(QString);
        void set_summoner_puuid(QString);
        void set_summoner_level(int);
        void set_is_data_valid(bool);
        void set_platform(QString);
        void set_region(QString);



};

#endif // SUMMONERDATA_H
