#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Include header files within this project
#include "./ApiKey.h"

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
        QString summoner;

        // Override
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

        // Getters from the ui
        QString get_platform_from_ui();
        QString get_region_from_ui();
        QString generate_summoner_api_url();



};
#endif // MAINWINDOW_H
