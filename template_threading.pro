QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS
TARGET = main

SOURCES += main.cpp
HEADERS += threading.h workers.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

