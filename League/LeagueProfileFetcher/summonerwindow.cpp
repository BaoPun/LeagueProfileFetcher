#include "./summonerwindow.h"
#include "./ui_summoner_profile_display.h"

SummonerProfile::SummonerProfile(QWidget *parent) : QMainWindow(parent), summoner_ui(new Ui::SummonerProfile){
    this->summoner_ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    this->hide();

    this->summoner_ui->centralwidget->installEventFilter(this);
    this->summoner_ui->summoner_input->installEventFilter(this);
    this->summoner_ui->tagline_input->installEventFilter(this);
    this->summoner_ui->centralwidget->setMouseTracking(true);

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

    this->champion_mastery_display = nullptr;
    this->solo_queue_image = nullptr;
    this->flex_queue_image = nullptr;
}

SummonerProfile::~SummonerProfile(){
    if(this->summoner_ui != nullptr){
        // Delete the dynamically allocated images
        this->delete_summoner_emblems();
        this->delete_summoner_mastered_champions_images();

        if(this->solo_queue_image != nullptr){
            delete this->solo_queue_image;
            this->solo_queue_image = nullptr;
        }
        if(this->flex_queue_image != nullptr){
            delete this->flex_queue_image;
            this->flex_queue_image = nullptr;
        }
        if(this->champion_mastery_display != nullptr){
            delete this->champion_mastery_display;
            this->champion_mastery_display = nullptr;
        }



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
 * @return the summoner name
 */
QString SummonerProfile::get_summoner(){
    return this->summoner;
}

/**
 * @brief Simple getter to return the riot id
 * @return the tagline (riot id)
 */
QString SummonerProfile::get_tagline(){
    return this->tagline;
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


void SummonerProfile::execute(){
    // Set focus to the input
    this->summoner_ui->summoner_input->setFocus();

    // Add a click event to the button when the submit button is clicked.
    connect(this->summoner_ui->submit_button, SIGNAL(clicked()), this, SLOT(process_and_clear_form()));

    this->show();
}

/**
 * @brief This slot is triggered when the submit button is clicked.
 */
void SummonerProfile::process_and_clear_form(){
    this->platform = this->get_platform_from_ui();
    this->region = this->get_region_from_ui();
    this->summoner = this->summoner_ui->summoner_input->toPlainText();
    this->tagline = this->summoner_ui->tagline_input->toPlainText();

    // IS the summoner name valid?
    if(this->summoner.length() < 3){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error, username is too short");
        msgBox.setText("Error, the summoner name input is invalid.");

        // Clear the inputs and set focus
        this->summoner_ui->summoner_input->setText("");
        this->summoner_ui->tagline_input->setText("");
        this->summoner_ui->summoner_input->setFocus();

        msgBox.exec();
        return;
    }

    // Is the tagline valid? (between 2 and 5 characters)
    if(this->tagline.isEmpty())
        this->tagline = this->platform;
    else if(this->summoner_ui->tagline_input->toPlainText().length() < 2 || this->summoner_ui->tagline_input->toPlainText().length() > 5){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error, tagline is not between 2 and 5 characters long.");
        msgBox.setText("Error, the tagline input is invalid.");

        // Clear the inputs and set focus
        //this->summoner_ui->summoner_input->setText("");
        this->summoner_ui->tagline_input->setText("");
        this->summoner_ui->tagline_input->setFocus();

        msgBox.exec();
        return;
    }


    // Input has been processed successfully, hide the window
    this->summoner_ui->summoner_input->setText("");
    this->summoner_ui->summoner_input->setFocus();
    this->summoner_ui->tagline_input->setText("");
    this->hide_window();
}

void SummonerProfile::hide_window(){
    this->hide();
    Q_EMIT this->windowHide();
}

void SummonerProfile::set_summoner_placeholder_label_text(QString new_text){
    this->summoner_ui->summoner_display->setText(new_text);
}

/**
 * @brief Delete the rank emblems from the summoner's profile.
 * A required call every time we search for a new summoner
 */
void SummonerProfile::delete_summoner_emblems(){
    // Delete all existing pointers first
    if(this->solo_queue_image != nullptr){
        delete this->solo_queue_image;
        this->solo_queue_image = nullptr;
    }
    if(this->flex_queue_image != nullptr){
        delete this->flex_queue_image;
        this->flex_queue_image = nullptr;
    }

    if(this->summoner_ui->solo_group->layout() != nullptr){
        QLayoutItem* item = nullptr;
        while(!this->summoner_ui->solo_group->layout()->isEmpty()){
            item = this->summoner_ui->solo_group->layout()->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete this->summoner_ui->solo_group->layout();
    }
    if(this->summoner_ui->flex_group->layout() != nullptr){
        QLayoutItem* item = nullptr;
        while(!this->summoner_ui->flex_group->layout()->isEmpty()){
            item = this->summoner_ui->flex_group->layout()->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete this->summoner_ui->flex_group->layout();
    }
}

/**
 * @brief Setting and displaying the summoner's rank emblems for both solo and flex queues.
 * @param solo_tier - a SummonerData object representing the summoner's solo q data
 * @param flex_tier - a SummonerData object representing the summoner's flex q data
 */
void SummonerProfile::set_summoner_rank_emblems(SummonerRank solo_tier, SummonerRank flex_tier){
    // Delete all existing pointers first
    this->delete_summoner_emblems();

    // Create a brand new horizontal box layout
    QBoxLayout* solo_layout = new QVBoxLayout();
    QBoxLayout* flex_layout = new QVBoxLayout();

    // Set up the solo queue data
    if(solo_tier.get_tier() != ""){
        QLabel* label = new QLabel();
        label->setText(
            solo_tier.get_tier() + " "
            + solo_tier.get_rank() + "\n"
            + QString::fromStdString(to_string(solo_tier.get_wins())) + " wins, "
            + QString::fromStdString(to_string(solo_tier.get_losses())) + " losses\n"
            + QString::fromStdString(to_string(solo_tier.get_league_points())) + " LP"
        );
        solo_layout->addWidget(label);
    }

    // Set up the solo queue emblem
    this->solo_queue_image = new QLabel();
    QImage solo_image;
    if(solo_tier.get_tier() != ""){
        solo_image.load("./../LeagueProfileFetcher/Ranked Emblems Latest/Rank=" + solo_tier.get_tier() + ".png");
        this->solo_queue_image->setToolTip(solo_tier.get_tier() + " Border");
    }
    else{
        solo_image.load("./../LeagueProfileFetcher/ICANT_KEKW.png");
        this->solo_queue_image->setToolTip("Non-ranked solo queue player ICANT KEKW");
    }
    solo_image = solo_image.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation);
    this->solo_queue_image->setPixmap(QPixmap::fromImage(solo_image));
    this->solo_queue_image->setScaledContents(true);
    solo_layout->addWidget(this->solo_queue_image);


    // Set up the flex queue data
    if(flex_tier.get_tier() != ""){
        QLabel* label = new QLabel();
        label->setText(
            flex_tier.get_tier() + " "
            + flex_tier.get_rank() + "\n"
            + QString::fromStdString(to_string(flex_tier.get_wins())) + " wins, "
            + QString::fromStdString(to_string(flex_tier.get_losses())) + " losses\n"
            + QString::fromStdString(to_string(flex_tier.get_league_points())) + " LP"
            );
        flex_layout->addWidget(label);
    }

    // Set up the flex queue emblem
    this->flex_queue_image = new QLabel();
    QImage flex_image;
    if(flex_tier.get_tier() != ""){
        flex_image.load("./../LeagueProfileFetcher/Ranked Emblems Latest/Rank=" + flex_tier.get_tier() + ".png");
        this->flex_queue_image->setToolTip(flex_tier.get_tier() + " Border");
    }
    else{
        flex_image.load("./../LeagueProfileFetcher/ICANT_KEKW.png");
        this->flex_queue_image->setToolTip("Non-ranked flex queue player ICANT KEKW");
    }
    flex_image = flex_image.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation);
    this->flex_queue_image->setPixmap(QPixmap::fromImage(flex_image));
    this->flex_queue_image->setScaledContents(true);
    flex_layout->addWidget(this->flex_queue_image);

    // And assign it to the respective solo/flex groups area.
    this->summoner_ui->solo_group->setLayout(solo_layout);
    this->summoner_ui->flex_group->setLayout(flex_layout);
}

/**
 * @brief Deletes the old layout from the championImageArea
 */
void SummonerProfile::delete_summoner_mastered_champions_images(){
    if(this->summoner_ui->championImageArea->layout() != nullptr){
        QLayoutItem* item = nullptr;
        while(!this->summoner_ui->championImageArea->layout()->isEmpty()){
            item = this->summoner_ui->championImageArea->layout()->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete this->summoner_ui->championImageArea->layout();
    }
}

/**
 * @brief Setting and displaying the summoner's top 7 (or less) most played champions.
 */
void SummonerProfile::set_summoner_champion_mastery_images(vector<QImage> images, vector<SummonerMastery> mastery){
    // First, delete the old championImageArea layout
    this->delete_summoner_mastered_champions_images();

    // Create a new layout to store each image
    QBoxLayout* layout = new QHBoxLayout();
    for(int i = 0; i < images.size(); i++){
        // Add a label pointer - which will hold the image itself.
        // The image is not a widget, but the label is (and the label can contain an image)
        QLabel* image_label = new QLabel();
        image_label->setPixmap(QPixmap::fromImage(images[i]));
        image_label->setScaledContents(true);
        image_label->setToolTip(
            mastery[i].get_champion_name() + "\nMastery Level "
            + QString::fromStdString(to_string(mastery[i].get_champion_level())) + "\n"
            + QString::fromStdString(to_string(mastery[i].get_champion_points())) + " points"
        );
        image_label->setObjectName(QString::fromStdString(to_string(mastery[i].get_champion_id())));
        image_label->installEventFilter(this);
        layout->addWidget(image_label);
    }

    // After adding all labels to the layout, set the new layout
    this->summoner_ui->championImageArea->setLayout(layout);
}

/**
 * @brief Emit a signal back to the ApiProcessor by passing in the champion that was clicked.
 * @param champion - name of the champion
 */
void SummonerProfile::send_champion_id_to_processor(int champion_id){
    Q_EMIT open_champion_window_signal(champion_id);
}

/**
 * @brief Filters through all possible events that are implemented on this function.
 * Specifically, this will look through the keypress event, and check to see if the "ENTER" key was pressed
 * @param object - the object we are messing with
 * @param event - the event to change the state of the object
 * @return true or false - required since this method is being overriden as a virtual declaration from the parent
 */
bool SummonerProfile::eventFilter(QObject *object, QEvent *event){
    /*// Hovering on the rank emblems or the images will change the cursor shape
    if(object->isWidgetType() && (this->summoner_ui->flex_group->inherits("QLabel") || this->summoner_ui->solo_group->inherits("QLabel")) && event->type() == QEvent::HoverEnter){
        this->summoner_ui->flex_group->setCursor(Qt::PointingHandCursor);
        return true;
    }*/

    // Mouse click event on any of the QLabels
    if(object->isWidgetType() && object->inherits("QLabel") && event->type() == QEvent::MouseButtonPress){
        this->send_champion_id_to_processor(object->objectName().toInt());
        return true;
    }

    // Any key press event
    else if((object == this->summoner_ui->summoner_input || object == this->summoner_ui->tagline_input || object == this->summoner_ui->centralwidget) && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Return){
            this->process_and_clear_form();
            return true;
        }

        // If the tab was pressed, move to either the summoner input or the tagline input
        // If the event was the summoner input, then move focus to the tagline input.
        // If the event was the tagline input, then move focus to the summoner input.
        else if(keyEvent->key() == Qt::Key_Tab){
            if(object == this->summoner_ui->summoner_input || object == this->summoner_ui->centralwidget){
                this->summoner_ui->tagline_input->setFocus();
                return true;
            }
            else if(object == this->summoner_ui->tagline_input){
                this->summoner_ui->summoner_input->setFocus();
                return true;
            }
        }

        // If CTRL and Q were pressed together, quit the program altogether.
        else if(keyEvent->key() == Qt::Key_Q && (keyEvent->modifiers() & Qt::ControlModifier)){
            this->close();
            return true;
        }
    }


    return false;
}
