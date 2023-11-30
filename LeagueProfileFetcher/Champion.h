#ifndef CHAMPION_H
#define CHAMPION_H

#include "./databaseInfo.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <vector>
#include <map>

using std::vector;
using std::map;


class Champion{
private:
    int id;
    QString name;
    QString image_url;
    QString spell_url;
    QString title;
    QString lore;
    QString resource_type;

public:
    Champion();

    int get_id();
    QString get_name();
    QString get_image_url();
    QString get_spell_url();
    QString get_title();
    QString get_lore();
    QString get_resource_type();

    void set_id(int);
    void set_name(QString);
    void set_image_url(QString);
    void set_spell_url(QString);
    void set_title(QString);
    void set_lore(QString);
    void set_resource_type(QString);
};

#endif // CHAMPION_H
