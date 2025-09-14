#include "AppController.h"

AppController::AppController(QObject *parent)
    : QObject{parent}
{
    m_weatherModel = new WeatherModel(this);
    m_weatherDayModel = new WeatherDayModel(m_weatherModel, this);
    m_lmManager = new LmManager(this);

    connect(m_weatherModel, &WeatherModel::currentWeatherChanged, this, &AppController::updateClothingSuggestion);

    //TODO: dont call fetch here do it in weatherModel
    m_weatherModel->fetchGeoData();
}

WeatherModel *AppController::weatherModel() const
{
    return m_weatherModel;
}

void AppController::setWeatherModel(WeatherModel *newWeatherModel)
{
    if (m_weatherModel == newWeatherModel)
        return;
    m_weatherModel = newWeatherModel;
    emit weatherModelChanged();
}

WeatherDayModel *AppController::weatherDayModel() const
{
    return m_weatherDayModel;
}

void AppController::setWeatherDayModel(WeatherDayModel *newWeatherDayModel)
{
    if (m_weatherDayModel == newWeatherDayModel)
        return;
    m_weatherDayModel = newWeatherDayModel;
    emit weatherDayModelChanged();
}

LmManager *AppController::lmManager() const
{
    return m_lmManager;
}

void AppController::setLmManager(LmManager *newLmManager)
{
    if (m_lmManager == newLmManager)
        return;
    m_lmManager = newLmManager;
    emit lmManagerChanged();
}

void AppController::updateClothingSuggestion()
{
    Weather *w = m_weatherModel->currentWeather();
    if(!w) return;

    m_lmManager->generateSuggestion(
        m_weatherModel->city(),
        w->desc(),
        w->dateTime(),
        w->temp(),
        w->feelTemp(),
        w->humidity(),
        w->wind(),
        w->clouds());
}
