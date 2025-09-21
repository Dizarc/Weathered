#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

#include "Weather-Service/WeatherModel.h"
#include "Weather-Service/WeatherDayModel.h"

#include "Lm-Service/lmManager.h"

#include "News-Service/NewsModel.h"

// For Communication between the classes
class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WeatherModel* weatherModel READ weatherModel WRITE setWeatherModel NOTIFY weatherModelChanged FINAL);
    Q_PROPERTY(WeatherDayModel* weatherDayModel READ weatherDayModel WRITE setWeatherDayModel NOTIFY weatherDayModelChanged FINAL);
    Q_PROPERTY(LmManager* lmManager READ lmManager WRITE setLmManager NOTIFY lmManagerChanged FINAL);
    Q_PROPERTY(NewsModel* newsModel READ newsModel WRITE setNewsModel NOTIFY newsModelChanged FINAL);

public:
    explicit AppController(QObject *parent = nullptr);

    WeatherModel *weatherModel() const;
    void setWeatherModel(WeatherModel *newWeatherModel);

    WeatherDayModel *weatherDayModel() const;
    void setWeatherDayModel(WeatherDayModel *newWeatherDayModel);

    LmManager *lmManager() const;
    void setLmManager(LmManager *newLmManager);

    NewsModel *newsModel() const;
    void setNewsModel(NewsModel *newNewsModel);

private slots:
    void updateClothingSuggestion();

signals:
    void weatherModelChanged();
    void weatherDayModelChanged();
    void lmManagerChanged();

    void newsModelChanged();

private:
    WeatherModel *m_weatherModel = nullptr;
    WeatherDayModel *m_weatherDayModel = nullptr;
    LmManager *m_lmManager = nullptr;
    NewsModel *m_newsModel = nullptr;
};

#endif // APPCONTROLLER_H
