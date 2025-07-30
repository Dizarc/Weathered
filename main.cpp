#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Weather-Service/WeatherApi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    WeatherApi *weatherApi = new WeatherApi(&app);
    qmlRegisterSingletonInstance("com.dizarc.WeatherApi", 1, 0, "WeatherApi", weatherApi);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("Weathered", "Main");

    return app.exec();
}
