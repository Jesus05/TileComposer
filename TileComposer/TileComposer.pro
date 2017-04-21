TEMPLATE = app

QT       += core

CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp

LIBS += -L../lib/
LIBS += -lTileComposerLib

DISTFILES += \
    libTileComposerLib.a \
    TileComposerLib.dll

HEADERS += \
    tilecomposerlib.h \
    tilecomposerlib_global.h
