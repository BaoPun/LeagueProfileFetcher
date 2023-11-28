#ifndef CHAMPIONWINDOW_H
#define CHAMPIONWINDOW_H

// Include header files within this project
#include "./CustomException.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class ChampionWindow; }
QT_END_NAMESPACE

class ChampionWindow : public QMainWindow{
private:
    Q_OBJECT
    Ui::ChampionWindow* champion_description_ui;
    QString champion_name;

    // Override
    bool eventFilter(QObject *, QEvent *) override; // Event filtering

public:
    ChampionWindow(QWidget* parent = nullptr, QString = "");
    ~ChampionWindow();

    // Getter and accessor for the champion name
    QString get_champion_name();
    void set_champion_name(QString);

    // Show the window
    void execute();
};

#endif // CHAMPIONWINDOW_H
