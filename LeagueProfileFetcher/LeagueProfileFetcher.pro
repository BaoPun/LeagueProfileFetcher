QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ApiProcessor.cpp \
    Champion.cpp \
    CustomException.cpp \
    championWindow.cpp \
    databaseInfo.cpp \
    main.cpp \
    mainwindow.cpp \
    staticData.cpp \
    summonerData.cpp \
    summonerMastery.cpp \
    summonerRank.cpp \
    summonerwindow.cpp

HEADERS += \
    ApiKey.h \
    ApiProcessor.h \
    Champion.h \
    CustomException.h \
    championWindow.h \
    databaseInfo.h \
    mainwindow.h \
    staticData.h \
    summonerData.h \
    summonerMastery.h \
    summonerRank.h \
    summonerwindow.h

FORMS += \
    champion_description.ui \
    mainwindow.ui \
    summoner_profile_display.ui

TRANSLATIONS += \
    LeagueProfileFetcher_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../Ranked Emblems Latest/Rank=Bronze.png \
    ../../../Ranked Emblems Latest/Rank=Bronze.png \
    ../../../Ranked Emblems Latest/Rank=Bronze.png \
    ../../../Ranked Emblems Latest/Rank=Challenger.png \
    ../../../Ranked Emblems Latest/Rank=Challenger.png \
    ../../../Ranked Emblems Latest/Rank=Challenger.png \
    ../../../Ranked Emblems Latest/Rank=Diamond.png \
    ../../../Ranked Emblems Latest/Rank=Diamond.png \
    ../../../Ranked Emblems Latest/Rank=Diamond.png \
    ../../../Ranked Emblems Latest/Rank=Emerald.png \
    ../../../Ranked Emblems Latest/Rank=Emerald.png \
    ../../../Ranked Emblems Latest/Rank=Emerald.png \
    ../../../Ranked Emblems Latest/Rank=Gold.png \
    ../../../Ranked Emblems Latest/Rank=Gold.png \
    ../../../Ranked Emblems Latest/Rank=Gold.png \
    ../../../Ranked Emblems Latest/Rank=Grandmaster.png \
    ../../../Ranked Emblems Latest/Rank=Grandmaster.png \
    ../../../Ranked Emblems Latest/Rank=Grandmaster.png \
    ../../../Ranked Emblems Latest/Rank=Iron.png \
    ../../../Ranked Emblems Latest/Rank=Iron.png \
    ../../../Ranked Emblems Latest/Rank=Iron.png \
    ../../../Ranked Emblems Latest/Rank=Master.png \
    ../../../Ranked Emblems Latest/Rank=Master.png \
    ../../../Ranked Emblems Latest/Rank=Master.png \
    ../../../Ranked Emblems Latest/Rank=Platinum.png \
    ../../../Ranked Emblems Latest/Rank=Platinum.png \
    ../../../Ranked Emblems Latest/Rank=Platinum.png \
    ../../../Ranked Emblems Latest/Rank=Silver.png \
    ../../../Ranked Emblems Latest/Rank=Silver.png \
    ../../../Ranked Emblems Latest/Rank=Silver.png \
    ../../../Ranked Emblems Latest/Tier Wings/Bronze.png \
    ../../../Ranked Emblems Latest/Tier Wings/Bronze.png \
    ../../../Ranked Emblems Latest/Tier Wings/Diamond.png \
    ../../../Ranked Emblems Latest/Tier Wings/Diamond.png \
    ../../../Ranked Emblems Latest/Tier Wings/Emerald.png \
    ../../../Ranked Emblems Latest/Tier Wings/Emerald.png \
    ../../../Ranked Emblems Latest/Tier Wings/Gold.png \
    ../../../Ranked Emblems Latest/Tier Wings/Gold.png \
    ../../../Ranked Emblems Latest/Tier Wings/Iron.png \
    ../../../Ranked Emblems Latest/Tier Wings/Iron.png \
    ../../../Ranked Emblems Latest/Tier Wings/Platinum.png \
    ../../../Ranked Emblems Latest/Tier Wings/Platinum.png \
    ../../../Ranked Emblems Latest/Tier Wings/Silver.png \
    ../../../Ranked Emblems Latest/Tier Wings/Silver.png \
    ../../../Ranked Emblems Latest/Wings/Bronze.png \
    ../../../Ranked Emblems Latest/Wings/Bronze.png \
    ../../../Ranked Emblems Latest/Wings/Challenger.png \
    ../../../Ranked Emblems Latest/Wings/Challenger.png \
    ../../../Ranked Emblems Latest/Wings/Diamond.png \
    ../../../Ranked Emblems Latest/Wings/Diamond.png \
    ../../../Ranked Emblems Latest/Wings/Emerald.png \
    ../../../Ranked Emblems Latest/Wings/Emerald.png \
    ../../../Ranked Emblems Latest/Wings/Gold.png \
    ../../../Ranked Emblems Latest/Wings/Gold.png \
    ../../../Ranked Emblems Latest/Wings/Grand.png \
    ../../../Ranked Emblems Latest/Wings/Grand.png \
    ../../../Ranked Emblems Latest/Wings/Iron.png \
    ../../../Ranked Emblems Latest/Wings/Iron.png \
    ../../../Ranked Emblems Latest/Wings/Master.png \
    ../../../Ranked Emblems Latest/Wings/Master.png \
    ../../../Ranked Emblems Latest/Wings/Platinum.png \
    ../../../Ranked Emblems Latest/Wings/Platinum.png \
    ../../../Ranked Emblems Latest/Wings/Silver.png \
    ../../../Ranked Emblems Latest/Wings/Silver.png \
    Ranked Emblems Latest/Rank=Bronze.png \
    Ranked Emblems Latest/Rank=Challenger.png \
    Ranked Emblems Latest/Rank=Diamond.png \
    Ranked Emblems Latest/Rank=Emerald.png \
    Ranked Emblems Latest/Rank=Gold.png \
    Ranked Emblems Latest/Rank=Grandmaster.png \
    Ranked Emblems Latest/Rank=Iron.png \
    Ranked Emblems Latest/Rank=Master.png \
    Ranked Emblems Latest/Rank=Platinum.png \
    Ranked Emblems Latest/Rank=Silver.png \
    Ranked Emblems Latest/Tier Wings/Bronze.png \
    Ranked Emblems Latest/Tier Wings/Diamond.png \
    Ranked Emblems Latest/Tier Wings/Emerald.png \
    Ranked Emblems Latest/Tier Wings/Gold.png \
    Ranked Emblems Latest/Tier Wings/Iron.png \
    Ranked Emblems Latest/Tier Wings/Platinum.png \
    Ranked Emblems Latest/Tier Wings/Silver.png \
    Ranked Emblems Latest/Wings/Bronze.png \
    Ranked Emblems Latest/Wings/Challenger.png \
    Ranked Emblems Latest/Wings/Diamond.png \
    Ranked Emblems Latest/Wings/Emerald.png \
    Ranked Emblems Latest/Wings/Gold.png \
    Ranked Emblems Latest/Wings/Grand.png \
    Ranked Emblems Latest/Wings/Iron.png \
    Ranked Emblems Latest/Wings/Master.png \
    Ranked Emblems Latest/Wings/Platinum.png \
    Ranked Emblems Latest/Wings/Silver.png

