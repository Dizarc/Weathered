#include "WeatherDayModel.h"

WeatherDayModel::WeatherDayModel(WeatherModel *sourceModel, QObject *parent)
    : QAbstractListModel{parent}
{
    m_sourceModel = sourceModel;

    connect(m_sourceModel, &WeatherModel::modelReset, this, &WeatherDayModel::updateWeatherData);
    connect(m_sourceModel, &WeatherModel::rowsInserted, this, &WeatherDayModel::updateWeatherData);

}

int WeatherDayModel::rowCount(const QModelIndex &parent) const
{
    return m_weatherDays.size();
}

QVariant WeatherDayModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() <0 || index.row() >= m_weatherDays.size())
        return {};

    WeatherDay *day = m_weatherDays[index.row()];

    switch(role) {
    case dayRole:
        return day->day();
    case weatherItemsRole:
        return QVariant::fromValue(day->weatherItems());
    default:
        return {};
    }
}

QHash<int, QByteArray> WeatherDayModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[dayRole] = "day";
    names[weatherItemsRole] = "weatherItems";

    return names;
}

//TODO: add an update to the day of the Model inside this function
void WeatherDayModel::updateWeatherData()
{
    beginResetModel();
    qDeleteAll(m_weatherDays);
    m_weatherDays.clear();

    QMap<QString,  QList<Weather*>> groupedData;

    QList<Weather*> weatherList = m_sourceModel->weatherList();
    QString date;

    for(int i = 0; i < weatherList.size(); i++) {
        date = weatherList[i]->dateTime().split(" ").first();

        groupedData[date].append(weatherList[i]);
    }

    for(auto i = groupedData.begin(); i != groupedData.end(); i++) {
        WeatherDay *day = new WeatherDay(this);

        day->setDay(i.key());
        day->setWeatherItems(i.value());

        m_weatherDays.append(day);
    }

    endResetModel();
}
