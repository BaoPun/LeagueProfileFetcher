#include "./summonerwindow.h"
#include "./ui_summoner_profile_display.h"

SummonerProfile::SummonerProfile(QWidget *parent) : QMainWindow(parent), summoner_ui(new Ui::SummonerProfile){
    this->summoner_ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    this->hide();

    this->summoner_ui->centralwidget->installEventFilter(this);
    this->summoner_ui->summoner_input->installEventFilter(this);
}

SummonerProfile::~SummonerProfile(){
    if(this->summoner_ui != nullptr){
        cout << "Deleting the summoner window (SummonerProfile class)..." << endl;
        delete this->summoner_ui;
        cout << "Deleted the summoner window (SummonerProfile class)" << endl;
    }
}

/**
 * @brief Simple getter to return the platform
 * @return the platform
 */
QString SummonerProfile::get_platform(){
    return this->platform;
}

/**
 * @brief Simple getter to return the region
 * @return the region
 */
QString SummonerProfile::get_region(){
    return this->region;
}

/**
 * @brief Simple getter to return the summoner
 * @return
 */
QString SummonerProfile::get_summoner(){
    return this->summoner;
}

/**
 * @brief After submitting the input form, get the platform from the dropdown
 * @return the platform as a QString
 */
QString SummonerProfile::get_platform_from_ui(){
    int index = this->summoner_ui->platform_input->currentIndex();
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
QString SummonerProfile::get_region_from_ui(){
    int index = this->summoner_ui->platform_input->currentIndex();
    if(index >= 0 && index <= 3)
        return "americas";
    else if(index >= 4 && index <= 7)
        return "europe";
    else if(index >= 8 && index <= 13)
        return "sea";
    else
        return "asia";
}

QString SummonerProfile::generate_summoner_api_url(){
    QString summoner_api_url;
    summoner_api_url.append("https://");
    summoner_api_url.append(this->platform);
    summoner_api_url.append(".api.riotgames.com/lol/summoner/v4/summoners/by-name/");
    summoner_api_url.append(this->summoner);
    summoner_api_url.append("?api_key=");
    summoner_api_url.append(QString::fromStdString(API_KEY));
    return summoner_api_url;
}

void SummonerProfile::execute(){
    // Set focus to the input
    this->summoner_ui->summoner_input->setFocus();

    // Add items to the dropdown and set North America to be the default value
    this->summoner_ui->platform_input->addItems(
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
    this->summoner_ui->platform_input->setCurrentIndex(1);

    // Add a click event to the button when the submit button is clicked.
    connect(this->summoner_ui->submit_button, SIGNAL(clicked()), this, SLOT(process_and_clear_form()));

    this->show();
}

void SummonerProfile::set_summoner_placeholder_label_text(QString new_text){
    this->summoner_ui->summoner_display->setText(new_text);
}

void SummonerProfile::set_summoner_solo_rank_label_text(QString new_text){
    this->summoner_ui->solo_label->setText(new_text);
}

void SummonerProfile::set_summoner_flex_rank_label_text(QString new_text){
    this->summoner_ui->flex_label->setText(new_text);
}

/**
 * @brief This slot is triggered when the submit button is clicked.
 */
void SummonerProfile::process_and_clear_form(){
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
}

void SummonerProfile::hide_window(){
    this->hide();
    Q_EMIT this->windowHide();
}

/**
 * @brief Filters through all possible events that are implemented on this function.
 * Specifically, this will look through the keypress event, and check to see if the "ENTER" key was pressed
 * @param object - the object we are messing with
 * @param event - the event to change the state of the object
 * @return true or false - required since this method is being overriden as a virtual declaration from the parent
 */
bool SummonerProfile::eventFilter(QObject *object, QEvent *event){
    if((object == this->summoner_ui->summoner_input || object == this->summoner_ui->centralwidget) && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Return){
            this->process_and_clear_form();
            return true;
        }
    }
    return false;
}
