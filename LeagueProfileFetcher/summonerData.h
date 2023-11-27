#ifndef SUMMONERDATA_H
#define SUMMONERDATA_H

#include "./databaseInfo.h"
#include "./summonerRank.h"
#include "./summonerMastery.h"
#include "./staticData.h"

class SummonerData{
    private:
        QString summoner_name;
        QString encrypted_summoner_id;
        QString summoner_puuid;
        QString platform, region;
        QString tagline;
        int summoner_level;
        bool is_data_valid;

        // Summoner specific data
        vector<SummonerRank> summoner_rank_data;
        vector<SummonerMastery> summoner_mastery_data;

    public:
        SummonerData();

        // Urls
        QString generate_riot_id_url();
        QString generate_summoner_api_url();

        // Data Processing
        void process_riot_data(QJsonObject);
        void process_summoner_data(QJsonObject);
        void process_rank_data(QJsonArray);
        void process_mastery_data(QJsonArray, PostgresDatabase*, StaticData);

        // Data reset
        void reset_all_rank_data();

        // Rank retrieval
        SummonerRank get_solo_queue_data();
        SummonerRank get_flex_queue_data();

        // Getters
        QString get_summoner_name();
        QString get_encrypted_summoner_id();
        QString get_summoner_puuid();
        QString get_tagline();
        int get_summoner_level();
        bool get_is_data_valid();
        QString get_platform();
        QString get_region();
        vector<int> get_all_mastery_champions();

        // Setters
        void set_summoner_name(QString);
        void set_encrypted_summoner_id(QString);
        void set_summoner_puuid(QString);
        void set_tagline(QString);
        void set_summoner_level(int);
        void set_is_data_valid(bool);
        void set_platform(QString);
        void set_region(QString);



};

#endif // SUMMONERDATA_H
