#include "Weather.h"

Weather::Weather(QObject *parent)
    : QObject{parent}
{

}

QString Weather::desc() const
{
    return m_desc;
}

void Weather::setDesc(const QString &newDesc)
{
    if(m_desc == newDesc)
        return;
    m_desc = newDesc;
    emit descChanged();
}

QUrl Weather::icon() const
{
    return m_icon;
}

void Weather::setIcon(const QUrl &newIcon)
{
    if(m_icon == newIcon)
        return;
    m_icon = newIcon;
    emit iconChanged();
}

QString Weather::dateTime() const
{
    return m_dateTime;
}

void Weather::setDateTime(const QString &newDateTime)
{
    if(m_dateTime == newDateTime)
        return;
    m_dateTime = newDateTime;
    emit dateTimeChanged();
}

double Weather::temp() const
{
    return m_temp;
}

void Weather::setTemp(const double &newTemp)
{
    if(m_temp == newTemp)
        return;
    m_temp = newTemp;
    emit tempChanged();
}

double Weather::feelTemp() const
{
    return m_feelTemp;
}

void Weather::setFeelTemp(const double &newFeelTemp)
{
    if(m_feelTemp == newFeelTemp)
        return;
    m_feelTemp = newFeelTemp;
    emit feelTempChanged();
}

double Weather::humidity() const
{
    return m_humidity;
}

void Weather::setHumidity(const double &newHumidity)
{
    if(m_humidity == newHumidity)
        return;
    m_humidity = newHumidity;
    emit humidityChanged();
}

double Weather::wind() const
{
    return m_wind;
}

void Weather::setWind(const double &newWind)
{
    if(m_wind == newWind)
        return;
    m_wind = newWind;
    emit windChanged();
}

double Weather::clouds() const
{
    return m_clouds;
}

void Weather::setClouds(const double &newClouds)
{
    if(m_clouds == newClouds)
        return;
    m_clouds = newClouds;
    emit cloudsChanged();
}
