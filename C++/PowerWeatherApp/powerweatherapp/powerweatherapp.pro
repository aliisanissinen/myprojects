QT += quick
QT += widgets
QT += network
QT += quick charts

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apireaders/apireader.cpp \
    apireaders/powerapireader.cpp \
    apireaders/weatherapireader.cpp \
    controllers/controller.cpp \
    controllers/powercontroller.cpp \
    controllers/weathercontroller.cpp \
    models/model.cpp \
    models/powermodel.cpp \
    models/weathermodel.cpp \
    powerchart.cpp \
    statistics.cpp \
    weatherchart.cpp \
    dataparser.cpp \
    main.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    apireaders/apireader.hh \
    apireaders/powerapireader.hh \
    apireaders/weatherapireader.hh \
    controllers/controller.hh \
    controllers/powercontroller.hh \
    controllers/weathercontroller.hh \
    dataparser.hh \
    models/model.hh \
    models/powermodel.hh \
    models/weathermodel.hh \
    powerchart.hh \
    statistics.hh \
    weatherchart.hh
