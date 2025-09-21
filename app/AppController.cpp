#include "AppController.h"

AppController::AppController(QObject *parent)
    : QObject{parent}
{
    m_weatherModel = new WeatherModel(this);
    m_weatherDayModel = new WeatherDayModel(m_weatherModel, this);
    m_lmManager = new LmManager(this);
    m_newsModel = new NewsModel(this);

    connect(m_weatherModel, &WeatherModel::currentWeatherChanged, this, &AppController::updateClothingSuggestion);
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

NewsModel *AppController::newsModel() const
{
    return m_newsModel;
}

void AppController::setNewsModel(NewsModel *newNewsModel)
{
    if (m_newsModel == newNewsModel)
        return;
    m_newsModel = newNewsModel;
    emit newsModelChanged();
}
