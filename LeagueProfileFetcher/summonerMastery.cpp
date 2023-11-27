#include "./summonerMastery.h"

SummonerMastery::SummonerMastery(){
    this->champion_id = -1;
    this->champion_points = -1;
    this->champion_level = -1;
    this->champion_name = "";
    this->summoner_puuid = "";
}

int SummonerMastery::get_champion_id(){
    return this->champion_id;
}

int SummonerMastery::get_champion_points(){
    return this->champion_points;
}

int SummonerMastery::get_champion_level(){
    return this->champion_level;
}

QString SummonerMastery::get_champion_name(){
    return this->champion_name;
}

QString SummonerMastery::get_summoner_puuid(){
    return this->summoner_puuid;
}

void SummonerMastery::set_champion_id(int champion_id){
    this->champion_id = champion_id;
}

void SummonerMastery::set_champion_points(int champion_points){
    this->champion_points = champion_points;
}

void SummonerMastery::set_champion_level(int champion_level){
    this->champion_level = champion_level;
}

void SummonerMastery::set_champion_name(QString champion_name){
    this->champion_name = champion_name;
}

void SummonerMastery::set_summoner_puuid(QString summoner_puuid){
    this->summoner_puuid = summoner_puuid;
}
