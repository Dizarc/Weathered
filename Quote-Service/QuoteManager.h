#ifndef QUOTEMANAGER_H
#define QUOTEMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>

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
    void handleReply();
signals:
    void quoteChanged();

private:
    QString m_quote;
    QNetworkAccessManager *m_manager;
    QNetworkRequest *m_request = new QNetworkRequest(URL);
    QNetworkReply *m_reply = nullptr;

    QUrl const URL; // TODO: Find the URL for llama.cpp
};

#endif // QUOTEMANAGER_H
