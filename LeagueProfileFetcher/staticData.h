#ifndef STATICDATA_H
#define STATICDATA_H

#include "./Champion.h"


class StaticData{
    private:
        string version;
        map<int, Champion> champion_data;
        map<int, map<string, string>> summoner_spell_data;
        map<int, map<string, string>> queue_data;
        map<int, map<string, string>> map_data;
        map<int, map<string, string>> item_data;

    public:
        StaticData();

        // Getters
        string get_version();
        QString get_champion_name_by_key(int);
        QString get_champion_image_url_by_key(int);
        QString get_champion_spell_url_by_key(int);
        QString get_champion_resource_name_by_key(int);
        string get_summoner_spell_name_by_key(int);
        string get_summoner_spell_description_by_key(int);

        // Setters
        void set_version(string, PostgresDatabase*);
        void set_champion_data(QJsonObject, PostgresDatabase*);
        void set_summoner_spell_data(QJsonObject, PostgresDatabase*);
        void set_queue_data(QJsonArray, PostgresDatabase*);
        void set_map_data(QJsonArray, PostgresDatabase*);
        void set_item_data(QJsonObject, PostgresDatabase*);
};

#endif // STATICDATA_H
