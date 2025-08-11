#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Weather-Service/WeatherModel.h"
#include "Weather-Service/WeatherDayModel.h"
#include "Weather-Service/Weather.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    WeatherModel *weatherModel = new WeatherModel(&app);
    qmlRegisterSingletonInstance("com.dizarc.WeatherModel", 1, 0, "WeatherModel", weatherModel);

    WeatherDayModel *weatherDayModel = new WeatherDayModel(weatherModel, &app);
    qmlRegisterSingletonInstance("com.dizarc.WeatherDayModel", 1, 0, "WeatherDayModel", weatherDayModel);

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
