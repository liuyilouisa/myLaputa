QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    airship.cpp \
    audiomanager.cpp \
    blockcloud.cpp \
    button.cpp \
    card.cpp \
    cloud.cpp \
    drop.cpp \
    fighter.cpp \
    gamewidget.cpp \
    lighteningcloud.cpp \
    main.cpp \
    map.cpp \
    menuwidget.cpp \
    other.cpp \
    pausewidget.cpp \
    plane.cpp \
    raincloud.cpp \
    rocket.cpp \
    shop.cpp \
    snowcloud.cpp \
    sun.cpp \
    suncloud.cpp

HEADERS += \
    airship.h \
    audiomanager.h \
    blockcloud.h \
    button.h \
    card.h \
    cloud.h \
    drop.h \
    fighter.h \
    gamewidget.h \
    lighteningcloud.h \
    map.h \
    menuwidget.h \
    other.h \
    pausewidget.h \
    plane.h \
    raincloud.h \
    rocket.h \
    shop.h \
    snowcloud.h \
    sun.h \
    suncloud.h

FORMS += \
    menuwidget.ui \
    pausewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
