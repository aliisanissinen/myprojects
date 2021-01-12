QT += testlib
QT -= gui

TARGET = StatisticsUnitTest

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/Game \
    $$PWD/../Course/CourseLib

DEPENDPATH += $$PWD/Game \
    $$PWD/../Course/CourseLib

SOURCES += StatisticsUnitTest.cpp \
    ../Game/statistics.cpp

HEADERS += ../Game/statistics.hh

DISTFILES += \
    ../Game/Pics/bus.png \
    ../Game/Pics/drone.png \
    ../Game/Pics/human.png \
    ../Game/Pics/stop.png \
    ../Game/Pics/stop2.png \
    ../Game/Pics/stop3.png \
    ../Game/Pics/top10Score.txt \
    ../Game/Pics/virus.jpg \
    ../Game/Pics/virus2.png

RESOURCES += \
    ../Game/pics.qrc
