QT += core
QT -= gui

TARGET = plugin-hotplug
TEMPLATE = lib
CONFIG += plugin

include($$PWD/../plugindepends/Plugindepends.pri)

HEADERS += \
    hotplugdetect.h \
    qpluginactivator.h

RESOURCES += \
    resource.qrc

SOURCES += \
    hotplugdetect.cpp \
    qpluginactivator.cpp


