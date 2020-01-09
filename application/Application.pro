QT -= gui

CONFIG += console
CONFIG -= app_bundle

include($$PWD/../plugindepends/Plugindepends.pri)

DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
        main.cpp \
        subscriber.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    subscriber.h
