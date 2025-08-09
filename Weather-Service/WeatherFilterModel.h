#ifndef WEATHERFILTERMODEL_H
#define WEATHERFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <QDate>
#include <QtQml>

#include "Weather-Service/WeatherModel.h"

class WeatherFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QDateTime filterDate READ filterDate WRITE setFilterDate NOTIFY filterDateChanged)

public:
    explicit WeatherFilterModel(WeatherModel *sourceModel, QObject *parent = nullptr);

    QDateTime filterDate() const;
    void setFilterDate(QDateTime &newDate);

signals:
    void filterDateChanged();

private:
    QDateTime m_filterDate;

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const override;
};

#endif // WEATHERFILTERMODEL_H
