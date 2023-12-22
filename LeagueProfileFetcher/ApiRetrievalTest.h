#ifndef APIRETRIEVALTEST_H
#define APIRETRIEVALTEST_H

#include "ApiProcessor.h"
#include <QObject>
#include <QTest>

/**
 * @brief This class will test out different API calls to ensure that everything is working as intended
 * in a specific order.  Some tests will be dependent on others.
 *
 * initTestCase() will be called before the first test function is executed.
 * initTestCase_data() will be called to create a global test data table.
 * cleanupTestCase() will be called after the last test function was executed.
 * init() will be called before each test function is executed.
 * cleanup() will be called after every test function.
 */

class ApiRetrievalTest : public QObject{
    Q_OBJECT
    private:
        ApiProcessor api_processor;
    private slots:
        void init(){
            qDebug() << "Test called.";
        }


        void cleanup(){
            api_processor.close_database_connection();
        }





    public:
        bool test_bad_api_key();
        bool test_good_api_key();


};

#endif // APIRETRIEVALTEST_H
