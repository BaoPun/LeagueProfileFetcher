#include "./summonerData.h"

SummonerData::SummonerData() : summoner_rank_data(2), summoner_mastery_data(10){
    this->encrypted_summoner_id = "";
    this->summoner_name = "";
    this->summoner_puuid = "";
    this->tagline = "";
    this->summoner_level = -1;
    this->is_data_valid = false;
    this->platform = "";
    this->region = "";
}

/**
 * @brief Given the summoner name and the tagline,
 * generate a URL that will, hopefully, capture the puuid, summoner name, and tagline.
 * @return The newly added Riot Id API URL.
 */
QString SummonerData::generate_riot_id_url(){
    QString riot_id_url;
    riot_id_url.append("https://");
    riot_id_url.append(this->region);
    riot_id_url.append(".api.riotgames.com/riot/account/v1/accounts/by-riot-id/");
    riot_id_url.append(this->get_summoner_name());
    riot_id_url.append("/");
    riot_id_url.append(this->get_tagline());
    riot_id_url.append("?api_key=");
    riot_id_url.append(API_KEY);
    return riot_id_url;
}

/**
 * @brief Generate the summoner api url given the puuid
 * @return a URL consisting of the summoner api url
 */
QString SummonerData::generate_summoner_api_url(){
    //https://{platform}.api.riotgames.com/lol/summoner/v4/summoners/by-puuid/{puuid}?api_key={API_KEY}
    QString summoner_api_url;
    summoner_api_url.append("https://");
    summoner_api_url.append(this->platform);
    summoner_api_url.append(".api.riotgames.com/lol/summoner/v4/summoners/by-puuid/");
    summoner_api_url.append(this->get_summoner_puuid());
    summoner_api_url.append("?api_key=");
    summoner_api_url.append(API_KEY);
    return summoner_api_url;
}

/**
 * @brief Process all the VALID data from the riot id api url.
 * @param json - json object to parse through.
 */
void SummonerData::process_riot_data(QJsonObject json){
    // New version only has 3 fields: puuid, summoner, tagline
    this->set_summoner_puuid(json.value("puuid").toString());
    this->set_summoner_name(json.value("gameName").toString());
    this->set_tagline(json.value("tagLine").toString());
}

/**
 * @brief Process all the VALID data from the summoner api url.
 * @param json - json object to parse through.
 */
void SummonerData::process_summoner_data(QJsonObject json){
    if(this->get_summoner_name() == "")
        this->set_summoner_name(json.value("name").toString());
    this->set_encrypted_summoner_id(json.value("id").toString());
    this->set_summoner_level(json.value("summonerLevel").toInt());

    // Ensure that the puuid from this call and the puuid from riot id api are the same
    if(this->get_summoner_puuid() == json.value("puuid").toString())
        this->set_is_data_valid(true);
    else
        cout << "WTF IS WRONG" << endl;
}

void SummonerData::reset_all_rank_data(){
    for(int i = 0; i < this->summoner_rank_data.size(); i++)
        this->summoner_rank_data[i].reset_rank_data();
}

/**
 * @brief Process all the VALID data from the summoner rank api url.
 * First, reset the rank data.
 * @param json - json array to parse through
 */
void SummonerData::process_rank_data(QJsonArray json){
    this->reset_all_rank_data();
    this->summoner_rank_data.resize(json.size());


    // DEBUG: print the json data
    //QJsonDocument doc;
    //doc.setArray(json);
    //cout << "Json rank data: " << doc.toJson(QJsonDocument::Indented).toStdString() << endl;

    // Due to inconsistencies with the ranked data, create another index denoting the actual count of ranked processes
    for(int i = 0, r = 0; i < json.size(); i++, r++){
        if(json[i].toObject()["queueType"].toString().toStdString() == "RANKED_SOLO_5x5" || json[i].toObject()["queueType"].toString().toStdString() == "RANKED_FLEX_SR")
            this->summoner_rank_data[r].process_rank_data(json[i].toObject());
    }
}

/**
 * @brief Process all the summoner's list of mastered champions.
 * For this project, only process the first 7
 * @param json - json array to parse through
 */
void SummonerData::process_mastery_data(QJsonArray json, PostgresDatabase* database, StaticData static_data){
    // DEBUG: print the json data
    //QJsonDocument doc;
    //doc.setArray(json);
    //cout << "Json mastery data: " << doc.toJson(QJsonDocument::Indented).toStdString() << endl;

    for(int i = 0; i < json.size() && i < 10; i++){
        // Champion id, points, and level are all obtained from json.
        // Same with the associated summoner puuid.
        this->summoner_mastery_data[i].set_champion_id(json[i].toObject()["championId"].toInt());
        this->summoner_mastery_data[i].set_champion_points((json[i].toObject()["championPoints"].toInt()));
        this->summoner_mastery_data[i].set_champion_level(json[i].toObject()["championLevel"].toInt());
        this->summoner_mastery_data[i].set_summoner_puuid(json[i].toObject()["puuid"].toString());

        // Either get the name from the database or from the static data
        if(database != nullptr)
            this->summoner_mastery_data[i].set_champion_name(database->get_champion_from_id(json[i].toObject()["championId"].toInt()));
        else
            this->summoner_mastery_data[i].set_champion_name(QString::fromStdString(static_data.get_champion_name_by_key(json[i].toObject()["championId"].toInt())));
    }
}

/**
 * @brief Find the solo q rank.
 * @return Return the solo q rank if found.
 */
SummonerRank SummonerData::get_solo_queue_data(){
    for(int i = 0; i < this->summoner_rank_data.size(); i++){
        if(this->summoner_rank_data[i].get_queue_type() == "RANKED_SOLO_5x5")
            return this->summoner_rank_data[i];
    }
    return SummonerRank();
}

/**
 * @brief Find the flex q rank.
 * @return Return the flex q rank if found.
 */
SummonerRank SummonerData::get_flex_queue_data(){
    for(int i = 0; i < this->summoner_rank_data.size(); i++){
        if(this->summoner_rank_data[i].get_queue_type() == "RANKED_FLEX_SR")
            return this->summoner_rank_data[i];
    }
    return SummonerRank();
}

/**
 * @brief Retrieve the champion ids of all mastered champions
 * @return
 */
vector<SummonerMastery> SummonerData::get_all_mastery_champions(){
    vector<SummonerMastery> result;
    for(int i = 0; i < this->summoner_mastery_data.size(); i++){
        if(this->summoner_mastery_data[i].get_summoner_puuid() == this->summoner_puuid)
            result.push_back(this->summoner_mastery_data[i]);
        else
            break;
    }
    return result;
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
 * @brief Getter to return the summoner's riot id
 * @return summoner's riot id
 */
QString SummonerData::get_tagline(){
    return this->tagline;
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
 * @brief Setter to change the summoner's riot id
 * @param riot_id - change the summoner's riot id
 */
void SummonerData::set_tagline(QString tagline){
    this->tagline = tagline;
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
