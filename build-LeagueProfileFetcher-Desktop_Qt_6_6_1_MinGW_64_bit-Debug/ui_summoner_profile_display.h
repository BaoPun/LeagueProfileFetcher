/********************************************************************************
** Form generated from reading UI file 'summoner_profile_display.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUMMONER_PROFILE_DISPLAY_H
#define UI_SUMMONER_PROFILE_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
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
    QGroupBox *solo_group;
    QGroupBox *flex_group;
    QScrollArea *championImageArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *enter_tagline_label;
    QTextEdit *tagline_input;
    QLabel *solo_placeholder;
    QLabel *flex_placeholder;
    QLabel *mastery_champions_label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SummonerProfile)
    {
        if (SummonerProfile->objectName().isEmpty())
            SummonerProfile->setObjectName("SummonerProfile");
        SummonerProfile->resize(933, 681);
        centralwidget = new QWidget(SummonerProfile);
        centralwidget->setObjectName("centralwidget");
        enter_summoner_label = new QLabel(centralwidget);
        enter_summoner_label->setObjectName("enter_summoner_label");
        enter_summoner_label->setGeometry(QRect(370, 470, 111, 16));
        summoner_input = new QTextEdit(centralwidget);
        summoner_input->setObjectName("summoner_input");
        summoner_input->setGeometry(QRect(330, 500, 251, 31));
        platform_input = new QComboBox(centralwidget);
        platform_input->setObjectName("platform_input");
        platform_input->setGeometry(QRect(70, 500, 151, 23));
        choose_platform_label = new QLabel(centralwidget);
        choose_platform_label->setObjectName("choose_platform_label");
        choose_platform_label->setGeometry(QRect(90, 470, 121, 20));
        submit_button = new QPushButton(centralwidget);
        submit_button->setObjectName("submit_button");
        submit_button->setGeometry(QRect(390, 560, 151, 41));
        summoner_display = new QLabel(centralwidget);
        summoner_display->setObjectName("summoner_display");
        summoner_display->setGeometry(QRect(270, 30, 361, 16));
        summoner_display->setAlignment(Qt::AlignCenter);
        solo_group = new QGroupBox(centralwidget);
        solo_group->setObjectName("solo_group");
        solo_group->setGeometry(QRect(140, 80, 271, 171));
        flex_group = new QGroupBox(centralwidget);
        flex_group->setObjectName("flex_group");
        flex_group->setGeometry(QRect(500, 80, 291, 171));
        championImageArea = new QScrollArea(centralwidget);
        championImageArea->setObjectName("championImageArea");
        championImageArea->setGeometry(QRect(140, 340, 651, 111));
        championImageArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        championImageArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        championImageArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 649, 109));
        championImageArea->setWidget(scrollAreaWidgetContents);
        enter_tagline_label = new QLabel(centralwidget);
        enter_tagline_label->setObjectName("enter_tagline_label");
        enter_tagline_label->setGeometry(QRect(700, 460, 45, 15));
        tagline_input = new QTextEdit(centralwidget);
        tagline_input->setObjectName("tagline_input");
        tagline_input->setGeometry(QRect(660, 500, 191, 31));
        solo_placeholder = new QLabel(centralwidget);
        solo_placeholder->setObjectName("solo_placeholder");
        solo_placeholder->setGeometry(QRect(230, 60, 91, 20));
        flex_placeholder = new QLabel(centralwidget);
        flex_placeholder->setObjectName("flex_placeholder");
        flex_placeholder->setGeometry(QRect(590, 60, 91, 16));
        mastery_champions_label = new QLabel(centralwidget);
        mastery_champions_label->setObjectName("mastery_champions_label");
        mastery_champions_label->setGeometry(QRect(420, 310, 81, 20));
        SummonerProfile->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SummonerProfile);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 933, 20));
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
        enter_summoner_label->setText(QCoreApplication::translate("SummonerProfile", "Summoner Name:", nullptr));
        summoner_input->setPlaceholderText(QCoreApplication::translate("SummonerProfile", "Enter summoner name:", nullptr));
        platform_input->setPlaceholderText(QCoreApplication::translate("SummonerProfile", "Choose platform:", nullptr));
        choose_platform_label->setText(QCoreApplication::translate("SummonerProfile", "Platform:", nullptr));
        submit_button->setText(QCoreApplication::translate("SummonerProfile", "Submit", nullptr));
        summoner_display->setText(QCoreApplication::translate("SummonerProfile", "Summoner Placeholder", nullptr));
        solo_group->setTitle(QString());
        flex_group->setTitle(QString());
        enter_tagline_label->setText(QCoreApplication::translate("SummonerProfile", "Tagline:", nullptr));
        tagline_input->setPlaceholderText(QCoreApplication::translate("SummonerProfile", "Enter tagline:", nullptr));
        solo_placeholder->setText(QCoreApplication::translate("SummonerProfile", "Solo Queue Rank", nullptr));
        flex_placeholder->setText(QCoreApplication::translate("SummonerProfile", "Flex Queue Rank", nullptr));
        mastery_champions_label->setText(QCoreApplication::translate("SummonerProfile", "Top Champions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SummonerProfile: public Ui_SummonerProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUMMONER_PROFILE_DISPLAY_H
