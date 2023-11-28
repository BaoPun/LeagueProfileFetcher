#include "./championWindow.h"
#include "./ui_champion_description.h"

ChampionWindow::ChampionWindow(QWidget* parent, QString champion_name) : QMainWindow(parent), champion_description_ui(new Ui::ChampionWindow){
    this->champion_description_ui->setupUi(this);
    this->champion_name = champion_name;
    this->hide();

    // Add the event filter to this window
    this->champion_description_ui->centralwidget->installEventFilter(this);

}

ChampionWindow::~ChampionWindow(){
    if(this->champion_description_ui != nullptr){
        cout << "Deleting the champion description window..." << endl;
        delete this->champion_description_ui;
        cout << "Deleted the champion description window!" << endl;
    }
}


// Getter and accessor for the champion name
// Retrieve the champion name
QString ChampionWindow::get_champion_name(){
    return this->champion_name;
}

// Set the champion name
// Also change the label
void ChampionWindow::set_champion_name(QString champion_name){
    this->champion_name = champion_name;
    this->champion_description_ui->champion_name_label->setText(this->champion_name + " Details");
}

/**
 * @brief Set up preliminary api calls before showing this window.
 */
void ChampionWindow::execute(){
    // First, ensure that this window NEVER has an empty champion name
    if(this->champion_name == ""){
        cout << "Error, this window should NEVER have an empty champion associated with this window.  Closing the app..." << endl;
        this->close();
        return;
    }
    this->show();
}



/**
 * @brief Filters through all possible events that are implemented on this function.
 * @param object - the object we are interacting with.
 * @param event - the event to change the state of the object.
 * @return true/false - true if we want the interaction to persist, false otherwise.
 */
bool ChampionWindow::eventFilter(QObject *object, QEvent *event){
    // CTRL Q to quit
    if(object == this->champion_description_ui->centralwidget && event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Q && (keyEvent->modifiers() & Qt::ControlModifier)){
            this->close();
            return true;
        }
    }




    return false;
}
