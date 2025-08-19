#include "QuoteManager.h"

QuoteManager::QuoteManager(QObject *parent)
    : QObject{parent}
{
    m_manager = new QNetworkAccessManager(this);

    m_request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}


QString QuoteManager::quote() const
{
    return m_quote;
}

void QuoteManager::setQuote(const QString &newQuote)
{
    if (m_quote == newQuote)
        return;
    m_quote = newQuote;
    emit quoteChanged();
}

void QuoteManager::generateQuote()
{
    //TODO: Find out if this is how llama.cpp receives requests
    QJsonObject payload;
    payload["prompt"] = "";
    payload["n_predict"] = 50;

    QJsonDocument doc(payload);
    QByteArray data =doc.toJson();

    m_manager->post(*m_request, data);

    connect(m_manager, &QNetworkAccessManager::finished, this, &QuoteManager::handleReply);
}

void QuoteManager::handleReply()
{
    if(m_reply->error() == QNetworkReply::NoError) {
        QByteArray response = m_reply->readAll();

        // TODO: Find how llama.cpp answers, parse that data, and change the quote for the QML side.

    } else
        qWarning() << "Error on LM request: " << m_reply->errorString();

    m_reply->deleteLater();
}
