#include "WeatherApi.h"

const QString ApiAccess::getApiKey()
{
    return QProcessEnvironment::systemEnvironment()
        .value("API_KEY", "");
}
const QString ApiAccess::getApiCityCountry()
{
    return QProcessEnvironment::systemEnvironment()
    .value("API_CITY_COUNTRY", "");
}

WeatherApi::WeatherApi(QObject *parent)
    : QObject{parent}
{
    m_info = "-C";
    m_manager = new QNetworkAccessManager(this);
}

QString WeatherApi::info() const
{
    return m_info;
}

void WeatherApi::fetchData()
{
    if(ApiAccess::getApiKey().isEmpty()) {
        qWarning() << "Environmental variable \"API_KEY\" is empty!";
        return;
    }

    if(m_reply) {
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = nullptr;
    }

    QUrlQuery geoQuery;

    geoQuery.addQueryItem("q", ApiAccess::getApiCityCountry());
    geoQuery.addQueryItem("limit", QString::number(1)); // limit one place
    geoQuery.addQueryItem("appid", ApiAccess::getApiKey());

    m_reply = m_manager->get(QNetworkRequest(ApiAccess::GEOCODE_URL + "direct?" + geoQuery.toString()));

    connect(m_reply, &QNetworkReply::finished, this, &WeatherApi::parseGeoData);

    // parseGeoData NEEDS to return the latitude and longitude for the next API request.
    // So find a way to do this with a simple yet correct way.
    // API request for weather info

    // Parse for the data
}

void WeatherApi::parseGeoData()
{
    if(m_reply->error() == QNetworkReply::NoError) {
        QByteArray data = m_reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

        // finish the rest of the parsing
    }
    else
        qWarning() << "Error from API reply: " + m_reply->errorString();
}

void WeatherApi::setInfo(const QString &data)
{
    if(m_info != data) {
        m_info = data;
        emit infoChanged();
    }
}
