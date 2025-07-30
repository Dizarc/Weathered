#include "WeatherApi.h"

WeatherApi::WeatherApi(QObject *parent)
    : QObject{parent}
{
    m_info = "-C";
    m_Manager = new QNetworkAccessManager(this);
}

QString WeatherApi::info() const
{
    return m_info;
}

void WeatherApi::fetchData()
{
    QString apiKey= "";
    QString city = "Athens";
    QString countryCode = "GRC"; //ISO 3166 code

    // API request for longitude and latitude

    // Parse for the data

    // API request for weather info

    // Parse for the data
}

void WeatherApi::setInfo(const QString &data)
{
    if(m_info != data) {
        m_info = data;
        emit infoChanged();
    }
}
