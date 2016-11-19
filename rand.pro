TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

SOURCES += main.cpp \
            star.cpp \
            textBox.cpp \
            moon.cpp

HEADERS += textBox.h \
            star.h \
            moon.h

