#ifndef DATABASEINFO_H
#define DATABASEINFO_H

#include "./ApiKey.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSql>

class PostgresDatabase{
    private:
        QSqlDatabase database;
        bool is_connected;

    public:
        PostgresDatabase();
        ~PostgresDatabase();

        void connect_to_database();
        void get_all_champions();
        QString get_champion_from_id(int);

};

#endif // DATABASEINFO_H
