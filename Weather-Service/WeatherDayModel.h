#ifndef WEATHERDAYMODEL_H
#define WEATHERDAYMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "Weather-Service/WeatherModel.h"
#include "Weather-Service/WeatherDay.h"

class WeatherDayModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        dayRole = Qt::UserRole + 1,
        weatherItemsRole
    };

    explicit WeatherDayModel(WeatherModel *sourceModel, QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void updateWeatherData();

private:
    QList<WeatherDay*> m_weatherDays;
    WeatherModel *m_sourceModel;
};

#endif // WEATHERDAYMODEL_H
