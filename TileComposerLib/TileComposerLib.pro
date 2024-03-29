#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T11:53:24
#
#-------------------------------------------------

CONFIG -= qt
#QT       -= core gui

TARGET = TileComposerLib
TEMPLATE = lib

DEFINES += TILECOMPOSERLIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += TILE_COMPOSER_EXPORT

SOURCES += tilecomposerlib.cpp \
    tilecomposer.cpp \
    tilepainter.cpp \
    lineargradient.cpp \
    linearvgradient.cpp \
    jsonloader.cpp

HEADERS += tilecomposerlib.h\
        tilecomposerlib_global.h \
    tilecomposer.h \
    tilepainter.h \
    lineargradient.h \
    linearvgradient.h \
    jsonloader.h \
    noisepack.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ../../include

LIBS += -L../../lib/

DESTDIR = ../lib/

win32 {
    CONFIG(release, debug|release):LIBS += -lnoise
    CONFIG(debug, debug|release):LIBS += -lnoised
}
