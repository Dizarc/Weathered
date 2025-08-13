#ifndef WEATHERDAY_H
#define WEATHERDAY_H

#include <QObject>
#include <QQmlListProperty>

#include "Weather-Service/Weather.h"

class WeatherDay : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString day READ day WRITE setDay NOTIFY dayChanged FINAL)
    Q_PROPERTY(QList<QObject*> weatherItems READ weatherItems NOTIFY weatherItemsChanged FINAL)

public:
    explicit WeatherDay(QObject *parent = nullptr);

    QString day() const;
    void setDay(const QString &newDay);

     QList<QObject*> weatherItems() const;
    void setWeatherItems(const  QList<Weather*> &newWeatherItems);

signals:
    void dayChanged();
    void weatherItemsChanged();

private:
    QString m_day;
    QList<Weather*> m_weatherItems;
};

#endif // WEATHERDAY_H
