TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt

include(entity_system/entity_system.pri)

SOURCES += \
        assetmanager.cpp \
    bullet.cpp \
    bulletmodel.cpp \
        command.cpp \
        commandsimplementation.cpp \
    game.cpp \
        gamemodel.cpp \
        gamewindow.cpp \
        inputhandle.cpp \
        main.cpp \
        mathcore.cpp \
    mousecommand.cpp \
        tank.cpp \
        tankmodel.cpp \
        tanktowermodel.cpp \
        tanktowerview.cpp \

HEADERS += \
    assetmanager.h \
    bullet.h \
    bulletmodel.h \
    command.h \
    commandsimplementation.h \
    game.h \
    gamemodel.h \
    gamewindow.h \
    inputhandle.h \
    mathcore.h \
    mousecommand.h \
    tank.h \
    tankmodel.h \
    tanktowermodel.h \
    tanktowerview.h \


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML/lib/ -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
else:unix: LIBS += -L$$PWD/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/SFML/include
DEPENDPATH += $$PWD/SFML/include

RESOURCES +=

DISTFILES += \
    entity_system/test_entity_system.pri \
    test_entity_system/test_entity_system.pri
