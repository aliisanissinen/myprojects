#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>

#include "powerchart.hh"
#include "weatherchart.hh"
#include "models/weathermodel.hh"
#include "models/powermodel.hh"
#include "apireaders/powerapireader.hh"
#include "apireaders/weatherapireader.hh"
#include "controllers/powercontroller.hh"
#include "controllers/weathercontroller.hh"
#include "statistics.hh"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    //Create all pointers to classes
    auto power {std::make_shared<PowerChart>()};
    auto powerModel {std::make_shared<PowerModel>()};

    auto powerController {std::make_shared<PowerController>()};
    auto weatherController {std::make_shared<WeatherController>()};

    auto weather {std::make_shared<WeatherChart>()};
    auto weatherModel {std::make_shared<WeatherModel>()};

    auto statistics {std::make_shared<Statistics>()};

    //Give chart pointer to model
    powerModel->setPowerChart(power);
    powerModel->setStatistics(statistics);

    weatherModel->setWeatherChart(weather);
    weatherModel->setStatistics(statistics);

    //Presentation of the required classes to QML side
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("powerchart", power.get());

    engine.rootContext()->setContextProperty("weatherchart", weather.get());

    engine.rootContext()->setContextProperty("powerModel", powerModel.get());

    engine.rootContext()->setContextProperty("weatherModel", weatherModel.get());

    engine.rootContext()->setContextProperty("statistics", statistics.get());

    powerController->setPowerModule(powerModel.get());
    powerController->setStatistics(statistics);

    weatherController->setWeatherModule(weatherModel.get());
    weatherController->setStatistics(statistics);

    powerController->setPowerModule(powerModel.get());
    engine.rootContext()->setContextProperty("powerController", powerController.get());

    weatherController->setWeatherModule(weatherModel.get());
    engine.rootContext()->setContextProperty("weatherController", weatherController.get());


    const QUrl url(QStringLiteral("qrc:/QML/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
