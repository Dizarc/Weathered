#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Weather-Service/WeatherModel.h"

/*
TODO: WeatherModel::fetchGeoData()
    Change the way it gets the values for the API stuff because of a comment in docs:
    "However, note that repeated calls to this function will recreate the QProcessEnvironment object, which is a non-trivial operation"

*/
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    WeatherModel *weatherModel = new WeatherModel(&app);
    qmlRegisterSingletonInstance("com.dizarc.WeatherModel", 1, 0, "WeatherModel", weatherModel);

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
