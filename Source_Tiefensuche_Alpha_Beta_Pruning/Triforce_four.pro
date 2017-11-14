TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    BotClass.cpp \
    FieldClass.cpp \
    GameStateClass.cpp \
    NodeClass.cpp \
    ParserClass.cpp \
    RatingClass.cpp

HEADERS +=\
    BotClass.h \
    FieldClass.h \
    GameStateClass.h \
    NodeClass.h \
    ParserClass.h \
    RatingClass.h

QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -static -lpthread
