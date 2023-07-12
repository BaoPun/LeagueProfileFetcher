/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

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

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *PlatformSelector;
    QTextEdit *SummonerInput;
    QLabel *textInputLabel;
    QLabel *label;
    QPushButton *SubmitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        PlatformSelector = new QComboBox(centralwidget);
        PlatformSelector->setObjectName("PlatformSelector");
        PlatformSelector->setGeometry(QRect(60, 240, 181, 31));
        PlatformSelector->setEditable(false);
        SummonerInput = new QTextEdit(centralwidget);
        SummonerInput->setObjectName("SummonerInput");
        SummonerInput->setGeometry(QRect(300, 240, 471, 31));
        SummonerInput->setAcceptRichText(false);
        textInputLabel = new QLabel(centralwidget);
        textInputLabel->setObjectName("textInputLabel");
        textInputLabel->setGeometry(QRect(410, 210, 151, 20));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 210, 101, 16));
        SubmitButton = new QPushButton(centralwidget);
        SubmitButton->setObjectName("SubmitButton");
        SubmitButton->setGeometry(QRect(260, 370, 211, 91));
        SubmitButton->setCheckable(true);
        SubmitButton->setChecked(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        SubmitButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        PlatformSelector->setCurrentText(QString());
        PlatformSelector->setPlaceholderText(QCoreApplication::translate("MainWindow", "Choose something...", nullptr));
        SummonerInput->setMarkdown(QString());
        SummonerInput->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        SummonerInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter something here:", nullptr));
        textInputLabel->setText(QCoreApplication::translate("MainWindow", "Enter a summoner name:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Choose a Platform:", nullptr));
#if QT_CONFIG(tooltip)
        SubmitButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Click this button to submit something :)</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        SubmitButton->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
