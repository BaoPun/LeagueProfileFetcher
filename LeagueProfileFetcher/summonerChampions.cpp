#include "./summonerChampions.h"
#include "./ui_summoner_champions_played.h"

SummonerChampions::SummonerChampions(QWidget *parent) : QMainWindow(parent), summoner_champions_ui(new Ui::SummonerChampions){

}


SummonerChampions::~SummonerChampions(){
    delete this->summoner_champions_ui;
}

/**
 * @brief This slot is triggered when the submit button is clicked.
 */
void SummonerChampions::process_and_clear_form(){
    /*
    this->platform = this->get_platform_from_ui();
    this->region = this->get_region_from_ui();
    this->summoner = QString::fromStdString(this->summoner_ui->summoner_input->toPlainText().toStdString());

    if(this->summoner_ui->summoner_input->toPlainText().toStdString().length() < 3){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error, username is too short");
        msgBox.setText("Error, the summoner name input is invalid.");

        // Clear the inputs and set focus
        this->summoner_ui->summoner_input->setText("");
        this->summoner_ui->summoner_input->setFocus();

        msgBox.exec();
        return;
    }

    // Input has been processed successfully, hide the window
    this->summoner_ui->summoner_input->setText("");
    this->summoner_ui->summoner_input->setFocus();
    this->hide_window();
    */
}


/**
 * @brief Filters through all possible events that are implemented on this function.
 * Specifically, this will look through the keypress event, and check to see if the "ENTER" key was pressed
 * @param object - the object we are messing with
 * @param event - the event to change the state of the object
 * @return true or false - required since this method is being overriden as a virtual declaration from the parent
 */
bool SummonerChampions::eventFilter(QObject *object, QEvent *event){
    /*
    if((object == this->summoner_ui->summoner_input || object == this->summoner_ui->centralwidget) && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Return){
            this->process_and_clear_form();
            return true;
        }
    }
    */
    return false;
}
