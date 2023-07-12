#ifndef STATICDATA_H
#define STATICDATA_H

#include "./ApiKey.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <vector>
#include <map>

using std::vector;
using std::map;

class StaticData{
    private:
        string version;
        map<int, map<string, string>> champion_data;
        map<int, map<string, string>> summoner_spell_data;
        map<int, map<string, string>> queue_data;
        map<int, map<string, string>> map_data;
        map<int, map<string, string>> item_data;

    public:
        StaticData();

        // Getters
        string get_version();
        string get_champion_name_by_key(int);
        string get_champion_url_by_key(int);
        string get_summoner_spell_name_by_key(int);
        string get_summoner_spell_description_by_key(int);

        // Setters
        void set_version(string);
        void set_champion_data(QJsonObject);
        void set_summoner_spell_data(QJsonObject);
        void set_queue_data(QJsonArray);
        void set_map_data(QJsonArray);
        void set_item_data(QJsonObject);
};

#endif // STATICDATA_H
