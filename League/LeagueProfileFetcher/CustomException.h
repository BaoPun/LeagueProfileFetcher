#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include "./ApiKey.h"

class CustomException : public QException{
private:
    QString error_message;
public:
    CustomException(QString);

    void print_message();
};

#endif // CUSTOMEXCEPTION_H
