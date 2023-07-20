#include "./summonerRank.h"

SummonerRank::SummonerRank(){
    this->rank = "";
    this->leaguePoints = -1;
    this->wins = -1;
    this->losses = -1;
    this->queue_type = "";
}

void SummonerRank::process_rank_data(QJsonObject json){
    this->set_rank(QString::fromStdString(json.value("tier").toString().toStdString() + " " + json.value("rank").toString().toStdString()));
    this->set_league_points(json.value("leaguePoints").toInt());
    this->set_wins(json.value("wins").toInt());
    this->set_losses(json.value("losses").toInt());
    this->set_queue_type(json.value("queueType").toString());
}

void SummonerRank::reset_rank_data(){
    this->rank = "";
    this->leaguePoints = -1;
    this->wins = -1;
    this->losses = -1;
    this->queue_type = "";
}

QString SummonerRank::get_rank() const{
    return this->rank;
}

int SummonerRank::get_league_points() const{
    return this->leaguePoints;
}

int SummonerRank::get_wins() const{
    return this->wins;
}

int SummonerRank::get_losses() const{
    return this->losses;
}

QString SummonerRank::get_queue_type() const{
    return this->queue_type;
}

void SummonerRank::set_rank(const QString &rank){
    this->rank = rank;
}

void SummonerRank::set_league_points(int leaguePoints){
    this->leaguePoints = leaguePoints;
}

void SummonerRank::set_wins(int wins){
    this->wins = wins;
}

void SummonerRank::set_losses(int losses){
    this->losses = losses;
}

void SummonerRank::set_queue_type(const QString &queue_type){
    this->queue_type = queue_type;
}
