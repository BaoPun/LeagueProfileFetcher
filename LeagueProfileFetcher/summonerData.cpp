#include "./summonerData.h"

SummonerData::SummonerData(){
    this->encrypted_summoner_id = "";
    this->summoner_name = "";
    this->summoner_puuid = "";
    this->summoner_level = -1;
    this->is_data_valid = false;
    this->platform = "";
    this->region = "";
}

/**
 * @brief Process all the VALID data from the summoner api url.
 * @param json - json object to parse through.
 */
void SummonerData::process_summoner_data(QJsonObject json){
    //cout << "Json object contents: " << QJsonDocument(json).toJson(QJsonDocument::Indented).toStdString() << endl;
    this->set_summoner_name(json.value("name").toString());
    this->set_encrypted_summoner_id(json.value("id").toString());
    this->set_summoner_puuid(json.value("puuid").toString());
    this->set_summoner_level(json.value("summonerLevel").toInt());
    this->set_is_data_valid(true);
}

void SummonerData::process_rank_data(QJsonArray json){
    cout << "Json data content for rank data" << endl;
}

/**
 * @brief Getter to return the summoner's IGN
 * @return summoner's name
 */
QString SummonerData::get_summoner_name(){
    return this->summoner_name;
}

/**
 * @brief Getter to return the summoner's encrypted id
 * @return summoner's encrypted id
 */
QString SummonerData::get_encrypted_summoner_id(){
    return this->encrypted_summoner_id;
}

/**
 * @brief Getter to return the summoner's puuid
 * @return summoner's puuid
 */
QString SummonerData::get_summoner_puuid(){
    return this->summoner_puuid;
}

/**
 * @brief Getter to return the summoner's level
 * @return summoner's level
 */
int SummonerData::get_summoner_level(){
    return this->summoner_level;
}

/**
 * @brief Getter to return whether or not the data is valid
 * @return True if the data is valid, False otherwise
 */
bool SummonerData::get_is_data_valid(){
    return this->is_data_valid;
}

/**
 * @brief Getter to return the summoner's platform
 * @return summoner's platform
 */
QString SummonerData::get_platform(){
    return this->platform;
}

/**
 * @brief Getter to return the summoner's region
 * @return summoner's region
 */
QString SummonerData::get_region(){
    return this->region;
}

/**
 * @brief Setter to change the summoner's summoner name
 * @param summoner_name - change the summoner name
 */
void SummonerData::set_summoner_name(QString summoner_name){
    this->summoner_name = summoner_name;
}

/**
 * @brief Setter to change the summoner's encrypted id
 * @param encrypted_summoner_id - change the summoner's encrypted id
 */
void SummonerData::set_encrypted_summoner_id(QString encrypted_summoner_id){
    this->encrypted_summoner_id = encrypted_summoner_id;
}

/**
 * @brief Setter to change the summoner's puuid
 * @param summoner_puuid - change the summoner's puuid
 */
void SummonerData::set_summoner_puuid(QString summoner_puuid){
    this->summoner_puuid = summoner_puuid;
}

/**
 * @brief Setter to change the summoner's level
 * @param summoner_level - change the summoner's level
 */
void SummonerData::set_summoner_level(int summoner_level){
    this->summoner_level = summoner_level;
}

/**
 * @brief Setter to change the flag of whether or not the data is valid
 * @param is_data_valid - change the validity flag
 */
void SummonerData::set_is_data_valid(bool is_data_valid){
    this->is_data_valid = is_data_valid;
}

/**
 * @brief Setter to change the summoner's platform
 * @param platform - change the summoner's platform
 */
void SummonerData::set_platform(QString platform){
    this->platform = platform;
}

/**
 * @brief Setter to change the summoner's region
 * @param region - change the summoner's region
 */
void SummonerData::set_region(QString region){
    this->region = region;
}
