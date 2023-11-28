#ifndef SUMMONERWINDOW_H
#define SUMMONERWINDOW_H

#include "./CustomException.h"

#include "./summonerData.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QLayout>
#include <QLayoutItem>
#include <QScrollBar>
#include <QScrollArea>


QT_BEGIN_NAMESPACE
namespace Ui { class SummonerProfile; }
QT_END_NAMESPACE

class SummonerProfile : public QMainWindow{
    private:
        Q_OBJECT
        Ui::SummonerProfile *summoner_ui;
        QString platform, region;
        QString summoner;
        QString tagline;

        // Dynamic elements
        QHBoxLayout* champion_mastery_display;
        QLabel* solo_queue_image;
        QLabel* flex_queue_image;

        // Getters from the ui
        QString get_platform_from_ui();
        QString get_region_from_ui();

        // Private methods that shouldn't be called publicly


        // Override
        bool eventFilter(QObject *, QEvent *) override; // Event filtering

    private slots:
        void process_and_clear_form();


    signals:
        void windowHide();
        void open_champion_window(QString);

    public:
        SummonerProfile(QWidget *parent = nullptr);
        ~SummonerProfile();

        // Getters
        QString get_platform();
        QString get_region();
        QString get_summoner();
        QString get_tagline();

        // Methods to show and hide the window
        void execute();
        void hide_window();

        // Auxilary methods
        void delete_summoner_emblems();
        void delete_summoner_mastered_champions_images();
        void send_champion_to_processor(QString);


        // Directly modifying the contents of the window
        void set_summoner_placeholder_label_text(QString);
        void set_summoner_rank_emblems(SummonerRank, SummonerRank);
        void set_summoner_champion_mastery_images(vector<QImage>, vector<SummonerMastery>);

};

#endif // SUMMONERWINDOW_H
