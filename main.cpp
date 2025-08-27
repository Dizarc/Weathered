#include <QGuiApplication>
#include <QQmlApplicationEngine>

//#include "Weather-Service/Weather.h"
//#include "Weather-Service/WeatherModel.h"
//#include "Weather-Service/WeatherDayModel.h"

//#include "Quote-Service/lmManager.h"

#include "AppController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //WeatherModel *weatherModel = new WeatherModel(&app);
    //qmlRegisterSingletonInstance("com.dizarc.WeatherModel", 1, 0, "WeatherModel", weatherModel);

    //WeatherDayModel *weatherDayModel = new WeatherDayModel(weatherModel, &app);
    //qmlRegisterSingletonInstance("com.dizarc.WeatherDayModel", 1, 0, "WeatherDayModel", weatherDayModel);

    //LmManager *lmManager = new LmManager(&app);
    //qmlRegisterSingletonInstance("com.dizarc.LmManager", 1, 0, "LmManager", lmManager);

    AppController *appController = new AppController(&app);
    qmlRegisterSingletonInstance("com.dizarc.AppController", 1, 0, "AppController", appController);

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
