#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

#include "Weather-Service/WeatherModel.h"
#include "Weather-Service/WeatherDayModel.h"

#include "Quote-Service/lmManager.h"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WeatherModel* weatherModel READ weatherModel WRITE setWeatherModel NOTIFY weatherModelChanged FINAL)
    Q_PROPERTY(WeatherDayModel* weatherDayModel READ weatherDayModel WRITE setWeatherDayModel NOTIFY weatherDayModelChanged FINAL)
    Q_PROPERTY(LmManager* lmManager READ lmManager WRITE setLmManager NOTIFY lmManagerChanged FINAL)

public:
    explicit AppController(QObject *parent = nullptr);

    WeatherModel *weatherModel() const;
    void setWeatherModel(WeatherModel *newWeatherModel);

    WeatherDayModel *weatherDayModel() const;
    void setWeatherDayModel(WeatherDayModel *newWeatherDayModel);

    LmManager *lmManager() const;
    void setLmManager(LmManager *newLmManager);

private slots:
    void updateClothingSuggestion();
    void refreshDailyQuote();

signals:
    void weatherModelChanged();
    void weatherDayModelChanged();

    void lmManagerChanged();

private:
    WeatherModel *m_weatherModel = nullptr;
    WeatherDayModel *m_weatherDayModel = nullptr;
    LmManager *m_lmManager = nullptr;
};

#endif // APPCONTROLLER_H
