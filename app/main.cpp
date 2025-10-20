#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "AppController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

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
