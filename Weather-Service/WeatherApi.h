#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QObject>

class WeatherApi : public QObject
{
    Q_OBJECT
public:
    explicit WeatherApi(QObject *parent = nullptr);

signals:
};

#endif // WEATHERAPI_H
