#include "./CustomException.h"

CustomException::CustomException(QString error_message){
    this->error_message = error_message;
}

void CustomException::print_message(){
    cout << "Error description: " << this->error_message.toStdString() << endl;
}
