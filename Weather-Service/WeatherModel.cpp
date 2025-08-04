#include "WeatherModel.h"

WeatherModel::WeatherModel(QObject *parent) : QAbstractListModel{parent}
{
    m_manager = new QNetworkAccessManager(this);

    connect(this, &WeatherModel::coordinatesReady, this, &WeatherModel::fetchWeatherData);
}

int WeatherModel::rowCount(const QModelIndex &parent) const
{
    return m_weatherList.size();
}

QVariant WeatherModel::data(const QModelIndex &index, int role) const
{
    QVariant val = {};

    if(index.isValid() && index.row() >= 0 && index.row() < m_weatherList.size()){
        Weather *weather = m_weatherList[index.row()];

        switch(role) {
        case cityRole:
            val = weather->city();
        case descRole:
            val = weather->desc();
        case iconRole:
            val = weather->icon();
        case dateTimeRole:
            val = weather->dateTime();
        case tempRole:
            val = weather->temp();
        case tempMinRole:
            val = weather->tempMin();
        case tempMaxRole:
            val = weather->tempMax();
        case humidityRole:
            val = weather->humidity();
        case windRole:
            val = weather->wind();
        case cloudsRole:
            val = weather->clouds();
        }
    }

    return val;
}

QHash<int, QByteArray> WeatherModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[cityRole] = "city";
    names[descRole] = "desc";
    names[iconRole] = "icon";
    names[dateTimeRole] = "dateTime";
    names[tempRole] = "temp";
    names[tempMinRole] = "tempMin";
    names[tempMaxRole] = "tempMax";
    names[humidityRole] = "humidity";
    names[windRole] = "wind";
    names[cloudsRole] = "clouds";

    return names;
}

void WeatherModel::fetchGeoData()
{
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

    connect(m_geoReply, &QNetworkReply::finished, this, &WeatherModel::parseGeoData);
}

void WeatherModel::parseGeoData()
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

// TODO: MISTAKE HERE WITH GIVING THE NAME!!
void WeatherModel::fetchWeatherData(const QString &name, const QString lat, const QString lon)
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

    connect(m_weatherReply, &QNetworkReply::finished, this, &WeatherModel::parseWeatherData);
}

void WeatherModel::parseWeatherData()
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

        Weather *weather = new Weather(this);

        QString cityname = "BLABLA";

        weather->setCity(cityname);

        weather->setTemp(mainObject["temp"].toDouble());
        weather->setTempMin(mainObject["temp_min"].toDouble());
        weather->setTempMax(mainObject["temp_max"].toDouble());

        weather->setHumidity(mainObject["humidity"].toDouble());
        weather->setWind(windObject["speed"].toDouble());
        weather->setClouds(cloudsObject["all"].toDouble());

        QJsonArray weatherArray = rootObject["weather"].toArray();
        if(!weatherArray.isEmpty()) {
            QJsonObject weatherObject = weatherArray.first().toObject();

            weather->setDesc(weatherObject["description"].toString());

            weather->setIcon(QUrl("https://openweathermap.org/img/wn/"
                                  + weatherObject["icon"].toString()
                                  + "@2x.png"));
        }

        setCurrentWeather(weather);

    }
    else
        qWarning() << "Error from geocoding API reply: " + m_weatherReply->errorString();

    m_weatherReply->deleteLater();
    m_weatherReply = nullptr;
}

void WeatherModel::setCurrentWeather(Weather *weather)
{
    clearList();
    addWeather(weather);
}

void WeatherModel::clearList()
{
    if(m_weatherList.isEmpty())
        return;

    beginResetModel();
    qDeleteAll(m_weatherList);
    m_weatherList.clear();
    endResetModel();
}

void WeatherModel::addWeather(Weather *weather)
{
    beginInsertRows(QModelIndex(), m_weatherList.length(), m_weatherList.length());
    m_weatherList.append(weather);
    endInsertRows();
    qDebug() << "INSERTED: " << weather->city() <<" "<< weather->desc();

}
