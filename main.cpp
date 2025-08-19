#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Weather-Service/Weather.h"
#include "Weather-Service/WeatherModel.h"
#include "Weather-Service/WeatherDayModel.h"

#include "Quote-Service/QuoteManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    WeatherModel *weatherModel = new WeatherModel(&app);
    qmlRegisterSingletonInstance("com.dizarc.WeatherModel", 1, 0, "WeatherModel", weatherModel);

    WeatherDayModel *weatherDayModel = new WeatherDayModel(weatherModel, &app);
    qmlRegisterSingletonInstance("com.dizarc.WeatherDayModel", 1, 0, "WeatherDayModel", weatherDayModel);

    QuoteManager *quoteManager = new QuoteManager(&app);
    qmlRegisterSingletonInstance("com.dizarc.QuoteManager", 1, 0, "QuoteManager", quoteManager);

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
