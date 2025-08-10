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

public:
    enum Roles {
        cityRole = Qt::UserRole + 1,
        descRole,
        iconRole,
        dateTimeRole,
        tempRole,
        tempMinRole,
        tempMaxRole,
        humidityRole,
        windRole,
        cloudsRole
    };

    explicit WeatherModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    QList<Weather*> weatherList() const;

public slots:
    void fetchGeoData();
    void fetchWeatherData(const QString &name,
                          const QString lat,
                          const QString lon);

private slots:
    void parseGeoData();
    void parseWeatherData();

    void setCurrentWeather(QList<Weather*> &forecast);
    void clearList();
    void addWeather(QList<Weather*> &forecast);

signals:
    void coordinatesReady(const QString &name,
                          const QString lat,
                          const QString lon);

private:
    QList<Weather*> m_weatherList;

    QNetworkAccessManager *m_manager;
    QNetworkReply *m_geoReply = nullptr;
    QNetworkReply *m_weatherReply = nullptr;
};

#endif // WEATHERMODEL_H
