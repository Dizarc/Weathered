#ifndef WEATHERMODEL_H
#define WEATHERMODEL_H

#include <QAbstractItemModel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProcessEnvironment>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "ApiAccess.hpp"
#include "Weather.h"

class WeatherModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged FINAL)
    Q_PROPERTY(Weather* currentWeather READ currentWeather WRITE setCurrentWeather NOTIFY currentWeatherChanged FINAL)

public:
    enum Roles {
        descRole = Qt::UserRole + 1,
        iconRole,
        dateTimeRole,
        tempRole,
        feelTempRole,
        humidityRole,
        windRole,
        cloudsRole
    };

    explicit WeatherModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    QList<Weather*> weatherList() const;

    void setCity(const QString &newCity);
    QString city() const;

    Weather *currentWeather() const;
    void setCurrentWeather(Weather *newCurrentWeather);

public slots:
    void fetchGeoData();
    void fetchWeatherData(const QString lat, const QString lon);

private slots:
    void parseGeoData();
    void parseWeatherData();

    void clearList();
    void addWeather(QList<Weather*> &forecast);

signals:
    void coordinatesReady(const QString lat, const QString lon);

    void cityChanged();

    void currentWeatherChanged();

private:
    QList<Weather*> m_weatherList;
    QString m_city;
    Weather *m_currentWeather = nullptr;

    QNetworkAccessManager *m_manager;
    QNetworkReply *m_geoReply = nullptr;
    QNetworkReply *m_weatherReply = nullptr;
};

#endif // WEATHERMODEL_H
