#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QUrl>

class Weather : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY descChanged FINAL);
    Q_PROPERTY(QUrl icon READ icon WRITE setIcon NOTIFY iconChanged FINAL);
    Q_PROPERTY(QString dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged FINAL);
    Q_PROPERTY(double temp READ temp WRITE setTemp NOTIFY tempChanged FINAL);
    Q_PROPERTY(double feelTemp READ feelTemp WRITE setFeelTemp NOTIFY feelTempChanged FINAL);
    Q_PROPERTY(double humidity READ humidity WRITE setHumidity NOTIFY humidityChanged FINAL);
    Q_PROPERTY(double wind READ wind WRITE setWind NOTIFY windChanged FINAL);
    Q_PROPERTY(double clouds READ clouds WRITE setClouds NOTIFY cloudsChanged FINAL);

public:
    explicit Weather(QObject *parent = nullptr);

    QString desc() const;
    void setDesc(const QString &newDesc);

    QUrl icon() const;
    void setIcon(const QUrl &newIcon);

    QString dateTime() const;
    void setDateTime(const QString &newDateTime);

    double temp() const;
    void setTemp(const double &newTemp);

    double feelTemp() const;
    void setFeelTemp(const double &newFeelTemp);

    double humidity() const;
    void setHumidity(const double &newHumidity);

    double wind() const;
    void setWind(const double &newWind);

    double clouds() const;
    void setClouds(const double &newClouds);

signals:
    void descChanged();
    void iconChanged();
    void dateTimeChanged();
    void tempChanged();
    void feelTempChanged();
    void humidityChanged();
    void windChanged();
    void cloudsChanged();

private:
    QString m_desc;
    QUrl m_icon;
    QString m_dateTime;
    double m_temp;
    double m_feelTemp;
    double m_humidity;
    double m_wind;
    int m_clouds;

};

#endif // WEATHER_H
