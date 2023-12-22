#include "./ApiRetrievalTest.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "LeagueProfileFetcher_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    */
    //cout << QDir::currentPath().toStdString() << endl;
    //QTEST_MAIN(ApiRetrievalTest);
    {   // Test in local scope.
        ApiRetrievalTest api_test;
        if(api_test.test_bad_api_key())
            cout << "TEST 1 PASSED." << endl;
        else
            cout << "TEST 2 FAILED." << endl;
        if(api_test.test_good_api_key())
            cout << "TEST 2 PASSED." << endl;
        else
            cout << "TEST 2 FAILED." << endl;
    }

    ApiProcessor api_processor_application;
    api_processor_application.execute_main_window();
    return a.exec();
}
