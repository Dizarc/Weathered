#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Weather-Service/WeatherModel.h"
#include "Weather-Service/WeatherFilterModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    WeatherModel *weatherModel = new WeatherModel(&app);
    qmlRegisterSingletonInstance("com.dizarc.WeatherModel", 1, 0, "WeatherModel", weatherModel);

    WeatherFilterModel *weatherFilterModel = new WeatherFilterModel(weatherModel, &app);
    qmlRegisterSingletonInstance("com.dizarc.WeatherFilterModel", 1, 0, "WeatherFilterModel", weatherFilterModel);

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
