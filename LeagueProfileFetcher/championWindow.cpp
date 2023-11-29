#include "./championWindow.h"
#include "./ui_champion_description.h"

ChampionWindow::ChampionWindow(QWidget* parent, QString champion_name) : QMainWindow(parent), champion_description_ui(new Ui::ChampionWindow){
    this->champion_description_ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

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

    // Set focus on the widget
    cout << "Champion entered: " << this->champion_name.toStdString() << endl;
    this->champion_description_ui->centralwidget->setFocus();

    // Also add a connection when the button is clicked
    connect(this->champion_description_ui->back_to_summoner_button, SIGNAL(clicked()), this, SLOT(go_back_to_summoner_window()));

    // Finally, show the window
    this->show();
}

/**
 * @brief Return the boolean value of "is_signaled" for use in the api processor
 * @return True or false, depending on the value of is_signaled.
 */
bool ChampionWindow::is_signal_triggered(){
    return this->is_signaled;
}

/**
 * @brief Once the api processor sees this signal, acknowledge it back to this class and disable the signal.
 */
void ChampionWindow::acknowledged_signal(){
    this->is_signaled = false;
}

/**
 * @brief Hide this window and then go back to the summoner window.  To go back, emit a signal.
 */
void ChampionWindow::go_back_to_summoner_window(){
    this->hide();
    this->is_signaled = true;
    Q_EMIT show_summoner_window_signal();
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
