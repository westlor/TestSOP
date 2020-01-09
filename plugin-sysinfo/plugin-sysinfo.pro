QT += core
QT -= gui

TARGET = plugin-sysinfo
TEMPLATE = lib
CONFIG += plugin

include($$PWD/../plugindepends/Plugindepends.pri)

HEADERS += \
    qpluginactivator.h

RESOURCES += \
    resource.qrc

SOURCES += \
    qpluginactivator.cpp


