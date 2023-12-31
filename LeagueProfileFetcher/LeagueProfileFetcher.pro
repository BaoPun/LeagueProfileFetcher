QT       += core gui network sql testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ApiProcessor.cpp \
    ApiRetrievalTest.cpp \
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
    ApiRetrievalTest.h \
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


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

