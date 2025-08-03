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

WeatherApi::WeatherApi(QObject *parent) : QObject{parent}
{
    m_info = "-C";

    m_manager = new QNetworkAccessManager(this);

    connect(this, &WeatherApi::coordinatesReady, this, &WeatherApi::fetchWeatherData);
}

QString WeatherApi::info() const
{
    return m_info;
}

void WeatherApi::fetchGeoData()
{
    //CHANGE THESE TWO! because of the comment in the documentation:
    //"However, note that repeated calls to this function will recreate the QProcessEnvironment object, which is a non-trivial operation"
    if(ApiAccess::getApiKey().isEmpty()) {
        qWarning() << "Environmental variable \"API_KEY\" is empty!";
        return;
    }
    if(ApiAccess::getApiCityCountry().isEmpty()) {
        qWarning() << "Environmental variable \"API_CITY_COUNTRY\" is empty!";
        return;
    }

    if(m_geoReply) {
        m_geoReply->abort();
        m_geoReply->deleteLater();
        m_geoReply = nullptr;
    }

    QUrlQuery query;

    query.addQueryItem("q", ApiAccess::getApiCityCountry());
    query.addQueryItem("limit", QString::number(1)); // limit to one place
    query.addQueryItem("appid", ApiAccess::getApiKey());

    m_geoReply = m_manager->get(QNetworkRequest(ApiAccess::GEOCODE_URL + "direct?" + query.toString()));

    connect(m_geoReply, &QNetworkReply::finished, this, &WeatherApi::parseGeoData);
}

void WeatherApi::parseGeoData()
{
    if(m_geoReply->error() == QNetworkReply::NoError) {
        QByteArray data = m_geoReply->readAll();

        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &parseError);

        if(parseError.error != QJsonParseError::NoError) {
            qWarning() << "Geocoding JSON parse error: " << parseError.errorString();
            return;
        }

        QJsonArray jsonArray = jsonDocument.array();

        if(!jsonArray.isEmpty()) {
            QJsonObject entry = jsonArray.first().toObject();

            QString name = entry["name"].toString();
            QString lat = QString::number(entry["lat"].toDouble());
            QString lon = QString::number(entry["lon"].toDouble());

            qDebug() << "name: " << name
                     << "lat: " << lat
                     << "lon: " << lon;

            emit coordinatesReady(name, lat, lon);
        }
    }
    else
        qWarning() << "Error from geocoding API reply: " + m_geoReply->errorString();

    m_geoReply->deleteLater();
    m_geoReply = nullptr;
}

void WeatherApi::fetchWeatherData(const QString &name, const QString lat, const QString lon)
{
    if(m_weatherReply) {
        m_weatherReply->abort();
        m_weatherReply->deleteLater();
        m_weatherReply = nullptr;
    }

    QUrlQuery query;

    query.addQueryItem("lat", lat);
    query.addQueryItem("lon", lon);
    query.addQueryItem("units", ApiAccess::UNITS);
    query.addQueryItem("appid", ApiAccess::getApiKey());

    m_weatherReply = m_manager->get(QNetworkRequest(ApiAccess::WEATHER_URL + "weather?" + query.toString()));

    connect(m_weatherReply, &QNetworkReply::finished, this, &WeatherApi::parseWeatherData);
}

void WeatherApi::parseWeatherData()
{
    if(m_weatherReply->error() == QNetworkReply::NoError) {
        QByteArray data = m_weatherReply->readAll();

        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &parseError);

        if(parseError.error != QJsonParseError::NoError) {
            qWarning() << "Weather JSON parse error: " << parseError.errorString();
            return;
        }

        QJsonObject rootObject = jsonDocument.object();

        //Main object contains temperatures and humidity
        QJsonObject mainObject = rootObject["main"].toObject();

        QJsonObject windObject = rootObject["wind"].toObject();
        QJsonObject cloudsObject = rootObject["clouds"].toObject();

        double temp = mainObject["temp"].toDouble();
        double tempMin = mainObject["temp_min"].toDouble();
        double tempMax = mainObject["temp_max"].toDouble();
        double humidity = mainObject["humidity"].toDouble();

        double windSpeed = windObject["speed"].toDouble();

        double cloudiness = cloudsObject["all"].toDouble();

        QJsonArray weatherArray = rootObject["weather"].toArray();
        QString weatherMain = "";
        QString weatherDesc = "";
        QString weatherIcon = "";

        if(!weatherArray.isEmpty()) {
            QJsonObject weatherObject = weatherArray.first().toObject();

            weatherMain = weatherObject["main"].toString();
            weatherDesc = weatherObject["description"].toString();
            weatherIcon = weatherObject["icon"].toString();
        }

        qDebug() << "Temp: " << temp
                 << "Min temp: " << tempMin
                 << "Max temp: " << tempMax
                 << "humidity: " << humidity
                 << "wind speed: " << windSpeed
                 << "cloudiness: " << cloudiness
                 << "Weather main: " << weatherMain
                 << "Weather description: " << weatherDesc
                 << "Weather icon: " << weatherIcon;

    }
    else
        qWarning() << "Error from geocoding API reply: " + m_weatherReply->errorString();

    m_weatherReply->deleteLater();
    m_weatherReply = nullptr;
}

void WeatherApi::setInfo(const QString &data)
{
    if(m_info != data) {
        m_info = data;
        emit infoChanged();
    }
}
