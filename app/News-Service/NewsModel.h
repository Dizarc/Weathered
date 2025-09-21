#ifndef NEWSMODEL_H
#define NEWSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../ApiAccess.hpp"
#include "News.h"

class NewsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        titleRole = Qt::UserRole + 1,
        descRole,
        imageRole,
        dateTimeRole,
        sourceRole
    };

    explicit NewsModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;


    QList<News*> newsList() const;
    void setNewsList(const QList<News*> &newNewsList);
private:
    void clearList();
    void addNews(QList<News*> &news);

public slots:
    void fetchData();

private slots:
    void  parseData();
signals:


private:
    QList<News*> m_newsList;

    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply = nullptr;
};

#endif // NEWSMODEL_H
