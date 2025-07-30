#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QNetworkAccessManager>
#include <QObject>

class WeatherApi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString info READ info NOTIFY infoChanged)

public:
    explicit WeatherApi(QObject *parent = nullptr);

    QString info() const;

public slots:
    void fetchData();

signals:
    void infoChanged();

private:
    void setInfo(const QString &data);

    QNetworkAccessManager *m_Manager;
    QString m_info;
};

#endif // WEATHERAPI_H
