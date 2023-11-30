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
        // Delete the dynamically allocated widgets on each layout
        this->delete_champion_skins_images();
        this->delete_champion_abilities_images();

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
 * @brief Delete the previous list of skins from the previous champion.
 */
void ChampionWindow::delete_champion_skins_images(){
    if(this->champion_description_ui->skins_list->layout() != nullptr){
        QLayoutItem* item = nullptr;
        while(!this->champion_description_ui->skins_list->layout()->isEmpty()){
            item = this->champion_description_ui->skins_list->layout()->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete this->champion_description_ui->skins_list->layout();
    }
}

/**
 * @brief Delete the previous list of spells from the previous champion.
 */
void ChampionWindow::delete_champion_abilities_images(){
    if(this->champion_description_ui->ability_list->layout() != nullptr){
        QLayoutItem* item = nullptr;
        while(!this->champion_description_ui->ability_list->layout()->isEmpty()){
            item = this->champion_description_ui->ability_list->layout()->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete this->champion_description_ui->ability_list->layout();
    }
}

/**
 * @brief Process the list of skins that the champion has.
 * @param skins - a vector of QImages to add to the skins UI.
 */
void ChampionWindow::process_champion_skins_images(vector<QImage> skins){
    // Before proceeding, delete the previous layout
    this->delete_champion_skins_images();

    // First, create a layout to add the skins to
    QBoxLayout* layout = new QHBoxLayout();

    // Second, iterate through each image, add the image to a new label, and add the new label to the layout
    for(int i = 0; i < skins.size(); i++){
        QLabel* skins_label = new QLabel();
        skins_label->setPixmap(QPixmap::fromImage(skins[i]));
        //skins_label->setScaledContents(true);
        //skins_label->setToolTip()
        //skins_label->setObjectName()
        layout->addWidget(skins_label);
    }

    // Finally, set the new layout on the skins area
    this->champion_description_ui->skins_list->setLayout(layout);
}

/**
 * @brief Process the list of spells + passive that the champion has.
 * @param abilities - a vector of QImages to add to the spells UI
 */
void ChampionWindow::process_champion_abilities_images(vector<QImage> abilities){
    // Before proceeding, delete the previous layout
    this->delete_champion_abilities_images();

    // First, create a layout to add the skins to
    QBoxLayout* layout = new QHBoxLayout();

    // Second, iterate through each image, add the image to a new label, and add the new label to the layout
    for(int i = 0; i < abilities.size(); i++){
        QLabel* ability_label = new QLabel();
        abilities[i] = abilities[i].scaled(75, 75, Qt::KeepAspectRatio, Qt::FastTransformation);
        ability_label->setPixmap(QPixmap::fromImage(abilities[i]));
        layout->addWidget(ability_label);
    }

    // Finally, set the new layout on the spells area
    this->champion_description_ui->ability_list->setLayout(layout);
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
