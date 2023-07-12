/********************************************************************************
** Form generated from reading UI file 'summoner_profile_display.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUMMONER_PROFILE_DISPLAY_H
#define UI_SUMMONER_PROFILE_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SummonerProfile
{
public:
    QWidget *centralwidget;
    QLabel *enter_summoner_label;
    QTextEdit *summoner_input;
    QComboBox *platform_input;
    QLabel *choose_platform_label;
    QPushButton *submit_button;
    QLabel *summoner_display;
    QLabel *rankImage;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SummonerProfile)
    {
        if (SummonerProfile->objectName().isEmpty())
            SummonerProfile->setObjectName("SummonerProfile");
        SummonerProfile->resize(800, 600);
        centralwidget = new QWidget(SummonerProfile);
        centralwidget->setObjectName("centralwidget");
        enter_summoner_label = new QLabel(centralwidget);
        enter_summoner_label->setObjectName("enter_summoner_label");
        enter_summoner_label->setGeometry(QRect(520, 370, 111, 16));
        summoner_input = new QTextEdit(centralwidget);
        summoner_input->setObjectName("summoner_input");
        summoner_input->setGeometry(QRect(440, 400, 251, 31));
        platform_input = new QComboBox(centralwidget);
        platform_input->setObjectName("platform_input");
        platform_input->setGeometry(QRect(160, 400, 151, 23));
        choose_platform_label = new QLabel(centralwidget);
        choose_platform_label->setObjectName("choose_platform_label");
        choose_platform_label->setGeometry(QRect(190, 370, 121, 20));
        submit_button = new QPushButton(centralwidget);
        submit_button->setObjectName("submit_button");
        submit_button->setGeometry(QRect(330, 480, 151, 41));
        summoner_display = new QLabel(centralwidget);
        summoner_display->setObjectName("summoner_display");
        summoner_display->setGeometry(QRect(210, 80, 361, 16));
        summoner_display->setAlignment(Qt::AlignCenter);
        rankImage = new QLabel(centralwidget);
        rankImage->setObjectName("rankImage");
        rankImage->setGeometry(QRect(360, 200, 45, 15));
        SummonerProfile->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SummonerProfile);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        SummonerProfile->setMenuBar(menubar);
        statusbar = new QStatusBar(SummonerProfile);
        statusbar->setObjectName("statusbar");
        SummonerProfile->setStatusBar(statusbar);

        retranslateUi(SummonerProfile);

        QMetaObject::connectSlotsByName(SummonerProfile);
    } // setupUi

    void retranslateUi(QMainWindow *SummonerProfile)
    {
        SummonerProfile->setWindowTitle(QCoreApplication::translate("SummonerProfile", "MainWindow", nullptr));
        enter_summoner_label->setText(QCoreApplication::translate("SummonerProfile", "Enter Summoner", nullptr));
        choose_platform_label->setText(QCoreApplication::translate("SummonerProfile", "Choose Platform", nullptr));
        submit_button->setText(QCoreApplication::translate("SummonerProfile", "Submit", nullptr));
        summoner_display->setText(QCoreApplication::translate("SummonerProfile", "Summoner Placeholder", nullptr));
        rankImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SummonerProfile: public Ui_SummonerProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUMMONER_PROFILE_DISPLAY_H
