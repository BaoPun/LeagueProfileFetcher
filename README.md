# LeagueProfileFetcher
This project uses the Qt Framework in order to create a widget that will help search for League of Legends players across multiple regions.

Upon a successful lookup, the initial window will show the summoner's solo queue and flex queue ranks, followed by their top 10 most played champions.

In addition, the user can click on the generated icons from the champions to get a better description of their abilities and to also view all their possible skins.

# Required Missing Files
This project has omitted 3 files: ApiKey.h, databaseInfo.h, and databaseInfo.cpp

For ApiKey.h, it stores your Riot Games API and multiple required libraries.  Note that you will need to generate your own Riot Games API key by following this link ([CLICK HERE](https://developer.riotgames.com/)).

Once you have your generated API KEY, please create your own ApiKey.h with the following structure:
## ApiKey.h FILE STRUCTURE
```
#ifndef APIKEY_H
#define APIKEY_H

#define API_KEY "YOUR_API_KEY_HERE"

#include <iostream>
#include <string>
#include <QException>
#include <regex>
#include <vector>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QString>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::regex;
using std::regex_replace;
using std::vector;

#endif // APIKEY_H
```

For both databaseInfo.h and databaseInfo.cpp, the database used is Postgres.  Thus, it is required that you have a Postgres database set up.  I used AWS to create a Postgres server, but you may use other RDS's as you wish. 
Before showing the file structures, I will show you the necessary tables that are needed for your own Postgres Database.

# Database Table Structure
You need to create the following tables:
1. Champion
2. Item
3. Map
4. Queue
5. SummonerSpell
6. Version

Here are the respective databaseInfo.h and databaseInfo.cpp files that you need:
## databaseInfo.h FILE STRUCTURE
```
#ifndef DATABASEINFO_H
#define DATABASEINFO_H

#include "./CustomException.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSql>

class PostgresDatabase{
private:
    QSqlDatabase database;
    bool is_connected;

    // Connect to the db.
    bool connect_to_database();


public:
    PostgresDatabase();
    ~PostgresDatabase();

    // Check the status of the connection
    bool is_database_connected();

    // GET methods
    int get_num_champions_database();
    int get_num_summoner_spells_database();
    int get_num_items_database();
    int get_num_queues_database();
    int get_num_maps_database();
    QString get_champion_from_id(int);
    QString get_item_from_id(int);
    QString get_version();
    QString get_champion_image_url_from_id(int);
    vector<QString> get_champion_image_urls_from_ids(QString values);

    // POST methods
    bool update_champion_data(QString = "");
    bool update_summoner_spell_data(QString = "");
    bool update_item_data(QString = "");
    bool update_queue_data(QString = "");
    bool update_map_data(QString = "");

    // PUT methods
    bool update_version(QString);

    // DELETE methods
    bool delete_champions();
    bool delete_summoner_spells();
    bool delete_items();
    bool delete_queues();
    bool delete_maps();

};

#endif // DATABASEINFO_H
```

## databaseInfo.cpp FILE STRUCTURE:
```
#include "./databaseInfo.h"

// Set up the connection details in the constructor
PostgresDatabase::PostgresDatabase(){
    this->database = QSqlDatabase::addDatabase("QPSQL");
    this->database.setDatabaseName("YOUR_DATABASE_NAME");
    this->database.setHostName("YOUR_HOST_NAME");
    this->database.setUserName("YOUR_USER_NAME");
    this->database.setPassword("YOUR_PASSWORD");
    this->database.setPort(YOUR_PORT);

    this->is_connected = this->connect_to_database();
}

// Automatic call to destructor will close the database connection
// If it was successfully opened via the constructor
PostgresDatabase::~PostgresDatabase(){
    if(this->is_connected){
        this->database.close();
        cout << "Postgres connection successfully closed." << endl;
    }
}

// Accessor: check if the database was successfully connected
bool PostgresDatabase::is_database_connected(){
    return this->is_connected;
}

// Attempt to connect to the database.
bool PostgresDatabase::connect_to_database(){
    return true ? this->database.open() : false;
}

// GET: return the # of champions
int PostgresDatabase::get_num_champions_database(){
    try{
        if(this->is_connected){
            QSqlQuery query;
            query.exec("select * from Champion where id > 0");
            return query.size();
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return -1;
    }
}

// GET: return the # of summoner spells
int PostgresDatabase::get_num_summoner_spells_database(){
    try{
        if(this->is_connected){
            QSqlQuery query;
            query.exec("select * from SummonerSpell where id > 0");
            return query.size();
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return -1;
    }
}

// GET: return the # of items
int PostgresDatabase::get_num_items_database(){
    try{
        if(this->is_connected){
            QSqlQuery query;
            query.exec("select * from Item");
            return query.size();
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return -1;
    }
}

// GET: return the # of queues
int PostgresDatabase::get_num_queues_database(){
    try{
        if(this->is_connected){
            QSqlQuery query;
            query.exec("select * from Queue");
            return query.size();
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return -1;
    }
}

// GET: return the # of maps
int PostgresDatabase::get_num_maps_database(){
    try{
        if(this->is_connected){
            QSqlQuery query;
            query.exec("select * from Map");
            return query.size();
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return -1;
    }
}

// GET: get a specific champion name from the database given the id
QString PostgresDatabase::get_champion_from_id(int id){
    try{
        if(this->is_connected){
            QSqlQuery query;
            query.prepare("select name from Champion where id = :id");
            query.bindValue(":id", id);
            query.exec();
            if(query.next())
                return query.value(0).toString();
            throw CustomException("No champion was found.");
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return QString("");
    }
}

// GET: get the current version from the database
QString PostgresDatabase::get_version(){
    try{
        if(this->is_connected){
            QSqlQuery query;
            query.exec("select version from version");
            if(query.next())
                return query.value(0).toString();
            throw CustomException("No version data was found.");
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return QString("");
    }
}

// GET: retrieve the associated champion's image url from the database given the id
QString PostgresDatabase::get_champion_image_url_from_id(int id){
    try{
        if(this->is_connected){
            QSqlQuery query;
            query.prepare("select image_url from Champion where id = :id");
            query.bindValue(":id", id);
            query.exec();
            if(query.next())
                return query.value(0).toString();
            throw CustomException("No image url was found.");
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return "";
    }
}

// GET: retrieve all image urls from the database given a list of ids stored as a vector
vector<QString> PostgresDatabase::get_champion_image_urls_from_ids(QString values){
    try{
        if(values == "")
            throw CustomException("There is no data to run the champion image rul query.");
        vector<QString> result;
        if(this->is_connected){
            QSqlQuery query;
            if(query.exec("select c.image_url from Champion c join (values " + values + ") as v(pos, id) on v.id = c.id order by v.pos")){
                while(query.next())
                    result.push_back(query.value(0).toString());
                return result;
            }
            throw CustomException("The champion image url select query failed to run.");
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return vector<QString>();
    }
}

// POST: update the old champion data with the new one
// By passing in a list of values corresponding to the new champion data
bool PostgresDatabase::update_champion_data(QString values){
    try{
        if(this->is_connected){
            if(values != ""){
                if(!this->database.transaction())
                    throw CustomException("Could not begin Champion POST transaction.");
                QSqlQuery query;
                if(query.exec("insert into Champion values " + values)){
                    this->database.commit();
                    return true;
                }
                throw CustomException("The champion insertion query could not be run.");
            }
            throw CustomException("Champion data up to date, no modifications required.");
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// POST: update the old summoner spell data with the new one
// By passing in a list of values corresponding to the new summoner spell data
bool PostgresDatabase::update_summoner_spell_data(QString values){
    try{
        if(this->is_connected){
            if(values != ""){
                if(!this->database.transaction())
                    throw CustomException("Could not begin Summoner Spell POST transaction.");
                QSqlQuery query;
                if(query.exec("insert into SummonerSpell values " + values)){
                    this->database.commit();
                    return true;
                }
                throw CustomException("The summoner spell insertion query could not be run.");
            }
            throw CustomException("Summoner Spell data up to date, no modifications required.");
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// POST: update the old item data with the new one
// By passing in a list of values corresponding to the new item data
bool PostgresDatabase::update_item_data(QString values){
    try{
        if(this->is_connected){
            if(values != ""){
                if(!this->database.transaction())
                    throw CustomException("Could not begin Item POST transaction.");
                QSqlQuery query;
                if(query.exec("insert into Item values " + values)){
                    this->database.commit();
                    return true;
                }
                throw CustomException("The item insertion query could not be run.");
            }
            throw CustomException("Item data up to date, no modifications required.");
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// POST: update the old queue data with the new one
// By passing in a list of values corresponding to the new queue data
bool PostgresDatabase::update_queue_data(QString values){
    try{
        if(this->is_connected){
            if(values != ""){
                if(!this->database.transaction())
                    throw CustomException("Could not begin Queue POST transaction.");
                QSqlQuery query;
                if(query.exec("insert into Queue values " + values)){
                    this->database.commit();
                    return true;
                }
                cout << "insert into Queue values " << values.toStdString() << endl;
                throw CustomException("The queue insertion query could not be run.");
            }
            throw CustomException("Queue data up to date, no modifications required.");
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// POST: update the old map data with the new one
// By passing in a list of values corresponding to the new map data
bool PostgresDatabase::update_map_data(QString values){
    try{
        if(this->is_connected){
            if(values != ""){
                if(!this->database.transaction())
                    throw CustomException("Could not being Map POST transaction.");
                QSqlQuery query;
                if(query.exec("insert into Map values " + values)){
                    this->database.commit();
                    return true;
                }
                throw CustomException("The map insertion query could not be run.");
            }
            throw CustomException("Map data up to date, no modifications required.");
        }
        throw CustomException("No database connection was established.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// PUT: update the version if it's out of date.
// Compare new version with old version
bool PostgresDatabase::update_version(QString new_version){
    try{
        if(this->is_connected){
            if(!this->database.transaction())
                throw CustomException("Could not begin Version PUT transaction.");
            QSqlQuery query;
            query.prepare("update Version set version = :version");
            query.bindValue(":version", new_version);
            if(query.exec()){
                this->database.commit();
                return true;
            }
            throw CustomException("The Version update query could not be run.");
        }
        throw CustomException("Database connection failed.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// DELETE: delete all champion data from the database
// Necessary to update with new data
bool PostgresDatabase::delete_champions(){
    try{
        if(this->is_connected){
            if(!this->database.transaction())
                throw CustomException("Could not begin delete transaction for champions.");
            QSqlQuery query;
            if(query.exec("delete from Champion")){
                this->database.commit();
                return true;
            }
            throw CustomException("Champion data deletion has failed.");
        }
        throw CustomException("Database connection failed.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// DELETE: delete all summoner spell data from the database
// Necessary to update with new data
bool PostgresDatabase::delete_summoner_spells(){
    try{
        if(this->is_connected){
            if(!this->database.transaction())
                throw CustomException("Could not begin delete transaction for summoner spells.");
            QSqlQuery query;
            if(query.exec("delete from SummonerSpell")){
                this->database.commit();
                return true;
            }
            throw CustomException("Summoner spell deletion has failed.");
        }
        throw CustomException("Database connection failed.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// DELETE: delete all item data from the database
// Necessary to update with new data
bool PostgresDatabase::delete_items(){
    try{
        if(this->is_connected){
            if(!this->database.transaction())
                throw CustomException("Could not begin delete transaction for items.");
            QSqlQuery query;
            if(query.exec("delete from Item")){
                this->database.commit();
                return true;
            }
            throw CustomException("Item deletion has failed.");
        }
        throw CustomException("Database connection failed.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// DELETE: delete all queue data from the database
// Necessary to update with new data
bool PostgresDatabase::delete_queues(){
    try{
        if(this->is_connected){
            if(!this->database.transaction())
                throw CustomException("Could not begin delete transaction for queues.");
            QSqlQuery query;
            if(query.exec("delete from Queue")){
                this->database.commit();
                return true;
            }
            throw CustomException("Queue deletion has failed.");
        }
        throw CustomException("Database connection failed.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}

// DELETE: delete all map data from the database
// Necessary to update with new data
bool PostgresDatabase::delete_maps(){
    try{
        if(this->is_connected){
            if(!this->database.transaction())
                throw CustomException("Could not begin delete transaction for maps.");
            QSqlQuery query;
            if(query.exec("delete from Map")){
                this->database.commit();
                return true;
            }
            throw CustomException("Map deletion has failed.");
        }
        throw CustomException("Database connection failed.");
    } catch(CustomException e){
        e.print_message();
        return false;
    }
}
```
