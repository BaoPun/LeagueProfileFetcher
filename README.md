# LeagueProfileFetcher
This project uses the Qt Framework in order to create a widget that will help search for League of Legends players across multiple regions.

Upon a successful lookup, the initial window will show the summoner's solo queue and flex queue ranks, followed by their top 10 most played champions.

In addition, the user can click on the generated icons from the champions to get a better description of their abilities and to also view all their possible skins.

# Required Missing Files
This project has omitted 3 files: ApiKey.h, databaseInfo.h, and databaseInfo.cpp

For ApiKey.h, it stores your Riot Games API and multiple required libraries.  Note that you will need to generate your own Riot Games API key by following this link ([CLICK HERE](https://developer.riotgames.com/)).

Once you have your generated API KEY, please create your own ApiKey.h with the following structure:
`
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

`
