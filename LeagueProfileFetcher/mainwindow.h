#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Include header files within this project
#include "./CustomException.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
private:
    Q_OBJECT
    Ui::MainWindow *ui;             // contains content from mainwindow.ui
    QString platform, region;
    QString summoner, tagline;

    // use to detect whether input was sent from this window
    // most of the time it will be from secondary window
    bool is_signal_from_main_window;

    // Getters from the ui
    QString get_platform_from_ui();
    QString get_region_from_ui();

    // Override
    bool is_main_window_used = true;
    bool eventFilter(QObject *, QEvent *) override; // Event filtering


private slots:
    void process_and_clear_form();

signals:
    void windowClose();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void execute();
    void close_window();

    // Getters
    QString get_platform();
    QString get_region();
    QString get_summoner();
    QString get_tagline();
    bool get_main_signal();

    void trigger_signal();



};
#endif // MAINWINDOW_H
