#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    this->ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    this->ui->centralwidget->installEventFilter(this);  // install the event filter for the widget
    this->ui->SummonerInput->installEventFilter(this);  // install the event filter for the textbox
}

MainWindow::~MainWindow(){
    if(this->ui != nullptr){
        cout << "Deleting the main window..." << endl;
        delete this->ui;
        cout << "Deleted the main window" << endl;
    }
}

/**
 * @brief Simple getter to return the platform
 * @return the platform
 */
QString MainWindow::get_platform(){
    return this->platform;
}

/**
 * @brief Simple getter to return the region
 * @return the region
 */
QString MainWindow::get_region(){
    return this->region;
}

/**
 * @brief Simple getter to return the summoner
 * @return
 */
QString MainWindow::get_summoner(){
    return this->summoner;
}

/**
 * @brief After submitting the input form, get the platform from the dropdown
 * @return the platform as a QString
 */
QString MainWindow::get_platform_from_ui(){
    int index = this->ui->PlatformSelector->currentIndex();
    switch(index){
    case 0:
        return "br1";
    case 1:
        return "na1";
    case 2:
        return "la1";
    case 3:
        return "la2";
    case 4:
        return "eun1";
    case 5:
        return "euw1";
    case 6:
        return "tr1";
    case 7:
        return "ru";
    case 8:
        return "oc1";
    case 9:
        return "ph2";
    case 10:
        return "sg2";
    case 11:
        return "th2";
    case 12:
        return "tw2";
    case 13:
        return "vn2";
    case 14:
        return "jp";
    case 15:
        return "kr";
    default:
        return "ICANT KEKW";
    }

    return "";
}

/**
 * @brief After submitting the input form, get the region from the dropdown
 * @return the region as a QString
 */
QString MainWindow::get_region_from_ui(){
    int index = this->ui->PlatformSelector->currentIndex();
    if(index >= 0 && index <= 3)
        return "americas";
    else if(index >= 4 && index <= 7)
        return "europe";
    else if(index >= 8 && index <= 13)
        return "sea";
    else
        return "asia";
}


/**
 * This function will add any additional event callers to the initial layout of the application.
 * For instance, if a button is submitted, then another event will trigger.
 */
void MainWindow::execute(){
    // Change the title of the window
    this->setWindowTitle("ICANT KEKW");

    // Set focus to the input
    this->ui->SummonerInput->setFocus();

    // Add items to the dropdown and set North America to be the default value
    this->ui->PlatformSelector->addItems(
        QStringList()
        << "Brazil"
        << "North America"
        << "Latin America1"
        << "Latin America2"
        << "Europe Northeast"
        << "Europe West"
        << "Turkey"
        << "Russia"
        << "Oceania"
        << "Phillipines"
        << "Singapore"
        << "Thailand"
        << "Taiwan"
        << "Vietnam"
        << "Japan"
        << "Korea"
    );
    this->ui->PlatformSelector->setCurrentIndex(1); // Index 1 = North America

    // Add a click event to the button when the submit button is clicked.
    QObject::connect(this->ui->SubmitButton, SIGNAL(clicked()), this, SLOT(process_and_clear_form()));

    // Show the widget
    this->show();
}





/**
 * @brief Given the platform and the summoner name input that was captured, generate the GET summoner name api.
 * @return a QString representing the url.
 */
QString MainWindow::generate_summoner_api_url(){
    QString summoner_api_url;
    summoner_api_url.append("https://");
    summoner_api_url.append(this->platform);
    summoner_api_url.append(".api.riotgames.com/lol/summoner/v4/summoners/by-name/");
    summoner_api_url.append(this->ui->SummonerInput->toPlainText());
    summoner_api_url.append("?api_key=");
    summoner_api_url.append(API_KEY);
    return summoner_api_url;
}

/**
 * Change the text after submitting the button/pressing ENTER on the search bar
 */
void MainWindow::process_and_clear_form(){
    // Set the platform and region and summoner
    this->platform = this->get_platform_from_ui();//.toStdString();
    this->region = this->get_region_from_ui();//.toStdString();
    this->summoner = this->ui->SummonerInput->toPlainText();//.toStdString();

    // If the input is invalid (less than 3 characters long), then print an error message
    if(this->summoner.toStdString().length() < 3){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error, username is too short");
        msgBox.setText("Error, the summoner name input is invalid.");

        // Clear the inputs and set focus
        this->ui->SummonerInput->setText("");
        this->ui->SummonerInput->setFocus();

        msgBox.exec();
        return;
    }

    // After input has been processed successfully, close the window
    this->close_window();
}

/**
 * @brief Close the window and then send a signal to the ApiProcessor
 */
void MainWindow::close_window(){
    this->close();
    Q_EMIT this->windowClose();    // once the window is hidden, emit this signal that will be triggered by ApiProcessor
}

/**
 * @brief Filters through all possible events that are implemented on this function.
 * Specifically, this will look through the keypress event, and check to see if the "ENTER" key was pressed
 * @param object - the object we are messing with
 * @param event - the event to change the state of the object
 * @return true or false - required since this method is being overriden as a virtual declaration from the parent
 */
bool MainWindow::eventFilter(QObject *object, QEvent *event){
    if((object == this->ui->SummonerInput || object == this->ui->centralwidget) && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Return){
            this->process_and_clear_form();
            return true;
        }
    }
    return false;
}
