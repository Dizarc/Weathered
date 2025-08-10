#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QUrl>

class Weather : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged);
    Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY descChanged);
    Q_PROPERTY(QUrl icon READ icon WRITE setIcon NOTIFY iconChanged);
    Q_PROPERTY(QString dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged);
    Q_PROPERTY(double temp READ temp WRITE setTemp NOTIFY tempChanged);
    Q_PROPERTY(double tempMin READ tempMin WRITE setTempMin NOTIFY tempMinChanged);
    Q_PROPERTY(double tempMax READ tempMax WRITE setTempMax NOTIFY tempMaxChanged);
    Q_PROPERTY(double humidity READ humidity WRITE setHumidity NOTIFY humidityChanged);
    Q_PROPERTY(double wind READ wind WRITE setWind NOTIFY windChanged);
    Q_PROPERTY(int clouds READ clouds WRITE setClouds NOTIFY cloudsChanged);

public:
    explicit Weather(QObject *parent = nullptr);

    QString city() const;
    void setCity(const QString &newCity);

    QString desc() const;
    void setDesc(const QString &newDesc);

    QUrl icon() const;
    void setIcon(const QUrl &newIcon);

    QString dateTime() const;
    void setDateTime(const QString &newDateTime);

    double temp() const;
    void setTemp(const double &newTemp);

    double tempMin() const;
    void setTempMin(const double &newTempMin);

    double tempMax() const;
    void setTempMax(const double &newTempMax);

    double humidity() const;
    void setHumidity(const double &newHumidity);

    double wind() const;
    void setWind(const double &newWind);

    int clouds() const;
    void setClouds(const int &newClouds);

signals:
    void cityChanged();
    void descChanged();
    void iconChanged();
    void dateTimeChanged();
    void tempChanged();
    void tempMinChanged();
    void tempMaxChanged();
    void humidityChanged();
    void windChanged();
    void cloudsChanged();

private:
    QString m_city;
    QString m_desc;
    QUrl m_icon;
    QString m_dateTime;
    double m_temp;
    double m_tempMin;
    double m_tempMax;
    double m_humidity;
    double m_wind;
    int m_clouds;

};

#endif // WEATHER_H
