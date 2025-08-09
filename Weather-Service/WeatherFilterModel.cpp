#include "WeatherFilterModel.h"

WeatherFilterModel::WeatherFilterModel(WeatherModel *sourceModel, QObject *parent)
    : QSortFilterProxyModel{parent}
{
    this->setSourceModel(sourceModel);
    this->setFilterKeyColumn(3);

    QDateTime date = QDateTime::currentDateTime();
    this->setFilterDate(date);

    this->setFilterRegularExpression(QRegularExpression(date.toString("yyyy-MM-dd HH:mm:ss")));
    qDebug() << date.toString("yyyy-MM-dd HH:mm:ss");
}

QDateTime WeatherFilterModel::filterDate() const
{
    return m_filterDate;
}

void WeatherFilterModel::setFilterDate(QDateTime &newDate)
{
    if(m_filterDate == newDate)
        return;
    m_filterDate = newDate;
    emit filterDateChanged();
}

/*
TODO: WeatherFilterModel::filterAcceptsRow()
    For some reason the filtering does not work and all the items show.
    Find where the issue is
*/
bool WeatherFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if(m_filterDate.isValid())
        return true;

    QModelIndex index = sourceModel()->index(sourceRow, filterKeyColumn(), sourceParent);
    QString dateTimeString = sourceModel()->data(index).toString();

    // Format from OpenWeatherMap API
    QDateTime dateTime = QDateTime::fromString(dateTimeString, "yyyy-MM-dd HH:mm:ss");

    if(!dateTime.isValid())
        return false;

    return dateTime.toString().contains(filterRegularExpression());
}

bool WeatherFilterModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    QString leftDateTimeString = sourceModel()->data(sourceLeft).toString();
    QString rightDateTimeString = sourceModel()->data(sourceRight).toString();

    QDateTime leftDateTime = QDateTime::fromString(leftDateTimeString, "yyyy-MM-dd HH:mm:ss");
    QDateTime rightDateTime = QDateTime::fromString(rightDateTimeString, "yyyy-MM-dd HH:mm:ss");

    if(!leftDateTime.isValid() || !rightDateTime.isValid())
        return QSortFilterProxyModel::lessThan(sourceLeft, sourceRight);

    QTime leftTime = leftDateTime.time();
    QTime rightTime = rightDateTime.time();

    return leftTime < rightTime;
}

