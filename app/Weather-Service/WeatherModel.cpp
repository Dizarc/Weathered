#include "WeatherModel.h"

WeatherModel::WeatherModel(QObject *parent) : QAbstractListModel{parent}
{
    m_manager = new QNetworkAccessManager(this);

    connect(this, &WeatherModel::coordinatesReady, this, &WeatherModel::fetchWeatherData);

    fetchGeoData();

    m_pruneTimer = new QTimer(this);
    m_pruneTimer->setInterval(60000); // 1 minute
    connect(m_pruneTimer, &QTimer::timeout, this, &WeatherModel::prunePastForecast);
    m_pruneTimer->start();

    m_fetchTimer = new QTimer(this);
    m_fetchTimer->setInterval(60000 * 60 * 24); // 24 hour
    connect(m_fetchTimer, &QTimer::timeout, this, &WeatherModel::fetchWeatherData);
    m_fetchTimer->start();
}

int WeatherModel::rowCount(const QModelIndex &parent) const
{
    return m_weatherList.size();
}

QVariant WeatherModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() <0 || index.row() >= m_weatherList.size())
        return {};

    Weather *weather = m_weatherList[index.row()];

    switch(role) {
    case descRole:
        return weather->desc();
    case iconRole:
        return weather->icon();
    case dateTimeRole:
        return weather->dateTime();
    case tempRole:
        return weather->temp();
    case feelTempRole:
        return weather->feelTemp();
    case humidityRole:
        return weather->humidity();
    case windRole:
        return weather->wind();
    case cloudsRole:
        return weather->clouds();
    default:
        return {};
    }
}

QHash<int, QByteArray> WeatherModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[descRole] = "desc";
    names[iconRole] = "icon";
    names[dateTimeRole] = "dateTime";
    names[tempRole] = "temp";
    names[feelTempRole] = "feelTemp";
    names[humidityRole] = "humidity";
    names[windRole] = "wind";
    names[cloudsRole] = "clouds";

    return names;
}

QList<Weather *> WeatherModel::weatherList() const
{
    return m_weatherList;
}

void WeatherModel::setCity(const QString &newCity)
{
    if(m_city == newCity)
        return;
    m_city = newCity;
    emit cityChanged();

}

QString WeatherModel::city() const
{
    return m_city;
}

Weather *WeatherModel::currentWeather() const
{
    return m_currentWeather;
}

void WeatherModel::setCurrentWeather(Weather *newCurrentWeather)
{
    if (m_currentWeather == newCurrentWeather)
        return;
    m_currentWeather = newCurrentWeather;
    emit currentWeatherChanged();
}

void WeatherModel::fetchGeoData()
{
    if(WeatherAPI::KEY.isEmpty()) {
        qWarning() << "Environmental variable \"WEATHER_API_KEY\" is empty!";
        return;
    }
    if(WeatherAPI::CITY_COUNTRY.isEmpty()) {
        qWarning() << "Environmental variable \"API_CITY_COUNTRY\" is empty!";
        return;
    }

    if(m_geoReply) {
        m_geoReply->abort();
        m_geoReply->deleteLater();
        m_geoReply = nullptr;
    }

    QUrlQuery query;

    query.addQueryItem("q", WeatherAPI::CITY_COUNTRY);
    query.addQueryItem("limit", QString::number(1)); // limit to one place
    query.addQueryItem("appid", WeatherAPI::KEY);

    m_geoReply = m_manager->get(QNetworkRequest(WeatherAPI::GEOCODE_URL + "direct?" + query.toString()));

    connect(m_geoReply, &QNetworkReply::finished, this, &WeatherModel::parseGeoData);
}

void WeatherModel::parseGeoData()
{
    if(m_geoReply->error() == QNetworkReply::NoError) {
        QByteArray data = m_geoReply->readAll();

        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &parseError);

        if(parseError.error == QJsonParseError::NoError) {
            QJsonArray jsonArray = jsonDocument.array();

            if(!jsonArray.isEmpty()) {
                QJsonObject entry = jsonArray.first().toObject();

                QString name = entry["name"].toString();
                QString lat = QString::number(entry["lat"].toDouble());
                QString lon = QString::number(entry["lon"].toDouble());

                setCity(name);
                m_lat = lat;
                m_lon = lon;
                emit coordinatesReady();
            }

        }else
            qWarning() << "Geocoding JSON parse error: " << parseError.errorString();
    }
    else
        qWarning() << "Error from geocoding API reply: " + m_geoReply->errorString();

    m_geoReply->deleteLater();
    m_geoReply = nullptr;
}

void WeatherModel::fetchWeatherData()
{
    if(m_weatherReply) {
        m_weatherReply->abort();
        m_weatherReply->deleteLater();
        m_weatherReply = nullptr;
    }

    QUrlQuery query;

    query.addQueryItem("lat", m_lat);
    query.addQueryItem("lon", m_lon);
    query.addQueryItem("units", WeatherAPI::UNITS);
    query.addQueryItem("appid", WeatherAPI::KEY);

    m_weatherReply = m_manager->get(QNetworkRequest(WeatherAPI::WEATHER_URL + "forecast?" + query.toString()));

    connect(m_weatherReply, &QNetworkReply::finished, this, &WeatherModel::parseWeatherData);
}

void WeatherModel::parseWeatherData()
{
    if(m_weatherReply->error() == QNetworkReply::NoError) {
        QByteArray data = m_weatherReply->readAll();

        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &parseError);

        if(parseError.error == QJsonParseError::NoError) {
            QJsonObject rootObject = jsonDocument.object();

            QJsonArray forecastArray = rootObject["list"].toArray();

            QList<Weather*> forecastList;

            for( const QJsonValue &value : forecastArray){

                QJsonObject entry = value.toObject();

                QJsonArray weatherArray = entry["weather"].toArray();
                QJsonObject weatherObject = weatherArray.at(0).toObject();

                QJsonObject mainObject = entry["main"].toObject();
                QJsonObject windObject = entry["wind"].toObject();
                QJsonObject cloudsObject = entry["clouds"].toObject();

                Weather *weather = new Weather(this);

                weather->setDesc(weatherObject["description"].toString());
                weather->setIcon(QUrl("https://openweathermap.org/img/wn/"
                                      + weatherObject["icon"].toString()
                                      + "@2x.png"));

                weather->setDateTime(entry["dt_txt"].toString());

                weather->setTemp(std::round(mainObject["temp"].toDouble() * 10.0) / 10.0);
                weather->setFeelTemp(std::round(mainObject["feels_like"].toDouble() * 10.0) / 10.0);
                weather->setHumidity(mainObject["humidity"].toDouble());
                weather->setWind(windObject["speed"].toDouble());
                weather->setClouds(cloudsObject["all"].toDouble());

                forecastList << weather;
            }

            clearList();
            addWeather(forecastList);

            prunePastForecast();
        }
        else
            qWarning() << "Weather JSON parse error: " << parseError.errorString();
    }
    else
        qWarning() << "Error from geocoding API reply: " + m_weatherReply->errorString();

    m_weatherReply->deleteLater();
    m_weatherReply = nullptr;
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

void WeatherModel::addWeather(QList<Weather*> &forecast)
{
    int start = m_weatherList.length();
    int end = start + forecast.length() - 1;

    beginInsertRows(QModelIndex(), start, end);

    m_weatherList.append(forecast);

    endInsertRows();

    setCurrentWeather(m_weatherList.at(0));
}

void WeatherModel::prunePastForecast()
{
    if(m_weatherList.isEmpty())
        return;

    QDateTime now = QDateTime::currentDateTime();
    int itemsToRemove = 0;

    for(Weather *weather : m_weatherList) {
        // API provides the dateTime in this format
        QDateTime itemDateTime = QDateTime::fromString(weather->dateTime(), "yyyy-MM-dd hh:mm:ss");

        // 3 hour window
        if(itemDateTime.addSecs(10800) < now)
            itemsToRemove++;
        else
            break; // Since API already sends the data sorted
    }

    if(itemsToRemove > 0) {
        beginRemoveRows(QModelIndex(), 0, itemsToRemove - 1);

        m_weatherList.remove(0, itemsToRemove);
        m_weatherList.squeeze();

        endRemoveRows();

        setCurrentWeather(m_weatherList.at(0));
    }

}
