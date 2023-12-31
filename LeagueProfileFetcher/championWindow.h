#ifndef CHAMPIONWINDOW_H
#define CHAMPIONWINDOW_H

// Include header files within this project
#include "./CustomException.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScrollBar>


QT_BEGIN_NAMESPACE
namespace Ui { class ChampionWindow; }
QT_END_NAMESPACE

class ChampionWindow : public QMainWindow{
private:
    Q_OBJECT
    Ui::ChampionWindow* champion_description_ui;
    QString champion_name;
    bool is_signaled = false;

    // Override
    bool eventFilter(QObject *, QEvent *) override; // Event filtering

private slots:
    void go_back_to_summoner_window();

signals:
    void show_summoner_window_signal();

public:
    ChampionWindow(QWidget* parent = nullptr, QString = "");
    ~ChampionWindow();

    // Getter and accessors
    bool is_signal_triggered();
    QString get_champion_name();
    void set_champion_name(QString);

    // Auxilary functions
    void acknowledged_signal();
    void delete_champion_skins_images();
    void delete_champion_abilities_images();
    void process_champion_skins_images(vector<QImage>, vector<QString>);
    void process_champion_abilities_images(vector<QImage>, vector<QString>);
    //void process_champion_data(QJsonArray, QJsonArray, QJsonObject);

    // Show the window
    void execute();
};

#endif // CHAMPIONWINDOW_H
