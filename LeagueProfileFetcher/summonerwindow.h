#ifndef SUMMONERWINDOW_H
#define SUMMONERWINDOW_H

#include "./ApiKey.h"

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class SummonerProfile; }
QT_END_NAMESPACE

class SummonerProfile : public QMainWindow{
    private:
        Q_OBJECT
        Ui::SummonerProfile *summoner_ui;
        QString platform, region;
        QString summoner;


        // Override
        bool eventFilter(QObject *, QEvent *) override; // Event filtering
        //void closeEvent(QCloseEvent *) override;

    private slots:
        void process_and_clear_form();

    signals:
        void windowHide();

    public:
        SummonerProfile(QWidget *parent = nullptr);
        ~SummonerProfile();

        // Getters
        QString get_platform();
        QString get_region();
        QString get_summoner();

        // Getters from the ui
        QString get_platform_from_ui();
        QString get_region_from_ui();
        QString generate_summoner_api_url();

        void execute();

        void hide_window();
        void set_summoner_placeholder_label_text(QString);
        void set_summoner_solo_rank_label_text(QString);
        void set_summoner_flex_rank_label_text(QString);

};

#endif // SUMMONERWINDOW_H
