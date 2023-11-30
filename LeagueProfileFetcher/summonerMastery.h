#ifndef SUMMONERMASTERY_H
#define SUMMONERMASTERY_H

#include "./CustomException.h"

class SummonerMastery{
    private:
        int champion_id;
        int champion_points;
        int champion_level;
        QString champion_name;
        QString summoner_puuid;

    public:
        SummonerMastery();

        int get_champion_id();
        int get_champion_points();
        int get_champion_level();
        QString get_champion_name();
        QString get_summoner_puuid();

        void set_champion_id(int);
        void set_champion_points(int);
        void set_champion_level(int);
        void set_champion_name(QString);
        void set_summoner_puuid(QString);


};

#endif // SUMMONERMASTERY_H
