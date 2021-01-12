TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    actors/actoritem.cpp \
    actors/busitem.cpp \
    actors/drone.cpp \
    actors/passengeritem.cpp \
    actors/stopitem.cpp \
    actors/vaccine.cpp \
    engine.cpp \
    main.cc \
    statistics.cpp \
    tampere.cpp \
    windows/dialog.cpp \
    windows/gamewindow.cpp

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

HEADERS += \
    actors/actoritem.h \
    actors/busitem.h \
    actors/drone.hh \
    actors/passengeritem.h \
    actors/stopitem.h \
    actors/vaccine.h \
    engine.hh \
    statistics.hh \
    tampere.h \
    windows/dialog.hh \
    windows/gamewindow.hh

FORMS += \
    dialog.ui \
    gamewindow.ui

RESOURCES += \
    pics.qrc

DISTFILES += \
    scoreData.txt \
    top10Score
