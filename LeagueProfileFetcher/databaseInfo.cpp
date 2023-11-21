#include "./databaseInfo.h"


PostgresDatabase::PostgresDatabase(){
    this->database = QSqlDatabase::addDatabase("QPSQL");
    this->database.setDatabaseName("postgres");
    this->database.setHostName("league-database.ckcpo20wzyxe.us-east-2.rds.amazonaws.com");
    this->database.setUserName("baop80_postgres");
    this->database.setPassword("leaguedatabase");
    this->database.setPort(5432);
    this->is_connected = false;

}

PostgresDatabase::~PostgresDatabase(){
    if(this->is_connected){
        this->database.close();
        cout << "Postgres connection successfully closed." << endl;
    }
}

void PostgresDatabase::connect_to_database(){
    if(!this->is_connected)
        this->is_connected = this->database.open();
}

void PostgresDatabase::get_all_champions(){
    if(this->is_connected){
        QSqlQuery query;
        if(query.exec("select * from Champion")){
            while(query.next()){
                cout << query.value(0).toInt() << "\t" << query.value(1).toString().toStdString() << endl;
            }
        }
        else{
            cout << "ERROR: " << query.lastError().text().toStdString() << endl;
        }
    }
}

QString PostgresDatabase::get_champion_from_id(int id){
    if(this->is_connected){
        QSqlQuery query;
        query.prepare("select name from Champion where id = :id");
        query.bindValue(":id", id);
        query.exec();
        if(query.next())
            return query.value(0).toString();
    }
    return QString("No champion was found");
}
