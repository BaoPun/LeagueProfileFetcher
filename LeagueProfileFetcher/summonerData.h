#ifndef SUMMONERDATA_H
#define SUMMONERDATA_H

#include "./summonerRank.h"
#include "./summonerMastery.h"

class SummonerData{
    private:
        QString summoner_name;
        QString encrypted_summoner_id;
        QString summoner_puuid;
        QString platform, region;
        int summoner_level;
        bool is_data_valid;
        vector<SummonerRank> summoner_rank_data;
        vector<SummonerMastery> summoner_mastery_data;


    public:
        SummonerData();

        // Data Processing
        void process_summoner_data(QJsonObject);
        void process_rank_data(QJsonArray);

        // Data reset
        void reset_all_rank_data();

        // Rank retrieval
        SummonerRank get_solo_queue_data();
        SummonerRank get_flex_queue_data();

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
