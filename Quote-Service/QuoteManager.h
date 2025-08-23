#ifndef QUOTEMANAGER_H
#define QUOTEMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>

#include "Weather-Service/ApiAccess.hpp"

class QuoteManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString quote READ quote WRITE setQuote NOTIFY quoteChanged FINAL)
public:
    explicit QuoteManager(QObject *parent = nullptr);

    QString quote() const;
    void setQuote(const QString &newQuote);

public slots:
    void generateQuote();

private slots:
    void handleReply(QNetworkReply *reply);
signals:
    void quoteChanged();

private:
    QString m_quote;
    QNetworkAccessManager *m_manager;
    QNetworkRequest *m_request = new QNetworkRequest(ModelAPI::LM_URL);
};

#endif // QUOTEMANAGER_H
