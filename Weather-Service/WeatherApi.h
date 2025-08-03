#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProcessEnvironment>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace ApiAccess {
    inline const QString GEOCODE_URL = "http://api.openweathermap.org/geo/1.0/";
    inline const QString WEATHER_URL = "https://api.openweathermap.org/data/2.5/";
    inline const QString UNITS = "metric";

    inline const QString getApiKey();
    inline const QString getApiCityCountry(); // City & Country(ISO 3166 code) divided by comma

}

class WeatherApi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString info READ info NOTIFY infoChanged)

public:
    explicit WeatherApi(QObject *parent = nullptr);

    QString info() const;

public slots:
    void fetchGeoData();
    void fetchWeatherData(const QString &name, const QString lat, const QString lon);

private slots:
    void parseGeoData();
    void parseWeatherData();

signals:
    void coordinatesReady(const QString &name, const QString lat, const QString lon);
    void infoChanged();

private:
    void setInfo(const QString &data);

    QNetworkAccessManager *m_manager;
    QNetworkReply *m_geoReply = nullptr;
    QNetworkReply *m_weatherReply = nullptr;
    QString m_info;
};

#endif // WEATHERAPI_H
