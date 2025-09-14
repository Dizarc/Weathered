#include "WeatherDay.h"

WeatherDay::WeatherDay(QObject *parent)
    : QObject{parent}
{}

QString WeatherDay::day() const
{
    return m_day;
}

void WeatherDay::setDay(const QString &newDay)
{
    if (m_day == newDay)
        return;
    m_day = newDay;
    emit dayChanged();
}

 QList<QObject*> WeatherDay::weatherItems() const
{
     QObjectList l;
    for(auto e: m_weatherItems){
         l << e;
    }
    return l;
}

void WeatherDay::setWeatherItems(const QList<Weather*> &newWeatherItems)
{
    if(m_weatherItems == newWeatherItems)
        return;
    m_weatherItems = newWeatherItems;
    emit weatherItemsChanged();
}
