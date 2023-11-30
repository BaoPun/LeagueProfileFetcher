/********************************************************************************
** Form generated from reading UI file 'champion_description.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAMPION_DESCRIPTION_H
#define UI_CHAMPION_DESCRIPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChampionWindow
{
public:
    QWidget *centralwidget;
    QLabel *champion_name_label;
    QPushButton *back_to_summoner_button;
    QScrollArea *skins_list;
    QWidget *scrollAreaWidgetContents;
    QLabel *skins_label;
    QLabel *ability_label;
    QScrollArea *ability_list;
    QWidget *scrollAreaWidgetContents_2;
    QTextBrowser *ability_description;
    QLabel *ability_description_label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChampionWindow)
    {
        if (ChampionWindow->objectName().isEmpty())
            ChampionWindow->setObjectName("ChampionWindow");
        ChampionWindow->resize(987, 700);
        centralwidget = new QWidget(ChampionWindow);
        centralwidget->setObjectName("centralwidget");
        champion_name_label = new QLabel(centralwidget);
        champion_name_label->setObjectName("champion_name_label");
        champion_name_label->setGeometry(QRect(450, 30, 131, 31));
        back_to_summoner_button = new QPushButton(centralwidget);
        back_to_summoner_button->setObjectName("back_to_summoner_button");
        back_to_summoner_button->setGeometry(QRect(420, 620, 141, 31));
        skins_list = new QScrollArea(centralwidget);
        skins_list->setObjectName("skins_list");
        skins_list->setGeometry(QRect(20, 100, 951, 181));
        skins_list->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        skins_list->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 949, 179));
        skins_list->setWidget(scrollAreaWidgetContents);
        skins_label = new QLabel(centralwidget);
        skins_label->setObjectName("skins_label");
        skins_label->setGeometry(QRect(470, 80, 45, 15));
        ability_label = new QLabel(centralwidget);
        ability_label->setObjectName("ability_label");
        ability_label->setGeometry(QRect(470, 320, 45, 15));
        ability_list = new QScrollArea(centralwidget);
        ability_list->setObjectName("ability_list");
        ability_list->setGeometry(QRect(240, 350, 521, 80));
        ability_list->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 519, 78));
        ability_list->setWidget(scrollAreaWidgetContents_2);
        ability_description = new QTextBrowser(centralwidget);
        ability_description->setObjectName("ability_description");
        ability_description->setGeometry(QRect(240, 490, 521, 121));
        ability_description_label = new QLabel(centralwidget);
        ability_description_label->setObjectName("ability_description_label");
        ability_description_label->setGeometry(QRect(460, 460, 71, 16));
        ChampionWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChampionWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 987, 20));
        ChampionWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ChampionWindow);
        statusbar->setObjectName("statusbar");
        ChampionWindow->setStatusBar(statusbar);

        retranslateUi(ChampionWindow);

        QMetaObject::connectSlotsByName(ChampionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChampionWindow)
    {
        ChampionWindow->setWindowTitle(QCoreApplication::translate("ChampionWindow", "MainWindow", nullptr));
        champion_name_label->setText(QString());
#if QT_CONFIG(tooltip)
        back_to_summoner_button->setToolTip(QCoreApplication::translate("ChampionWindow", "Click to go back to the Summoner Window.", nullptr));
#endif // QT_CONFIG(tooltip)
        back_to_summoner_button->setText(QCoreApplication::translate("ChampionWindow", "Go Back To Summoner", nullptr));
        skins_label->setText(QCoreApplication::translate("ChampionWindow", "Skins", nullptr));
        ability_label->setText(QCoreApplication::translate("ChampionWindow", "Abilities", nullptr));
        ability_description_label->setText(QCoreApplication::translate("ChampionWindow", "Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChampionWindow: public Ui_ChampionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAMPION_DESCRIPTION_H
