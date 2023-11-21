#ifndef SUMMONERCHAMPIONS_H
#define SUMMONERCHAMPIONS_H

#include "./ApiKey.h"

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class SummonerChampions; }
QT_END_NAMESPACE

class SummonerChampions : public QMainWindow{
    private:
        Q_OBJECT
        Ui::SummonerChampions *summoner_champions_ui;
        QString champion;

        // Override
        bool eventFilter(QObject *, QEvent *) override; // Event filtering

    public:
        SummonerChampions(QWidget *parent = nullptr);
        ~SummonerChampions();

        void process_and_clear_form();


};


#endif // SUMMONERCHAMPIONS_H
