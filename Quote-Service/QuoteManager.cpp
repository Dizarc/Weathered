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
    //TODO: Create an amazing prompt
    QJsonObject payload;
    payload["prompt"] = "write me a short happy quote";
    payload["n_predict"] = 50;

    QJsonDocument doc(payload);
    QByteArray data =doc.toJson();

    m_manager->post(*m_request, data);

    connect(m_manager, &QNetworkAccessManager::finished, this, &QuoteManager::handleReply);
}

// TODO: get the reply back from the LM
// (possible issue of crash is the fact that handleReply needs a QNetworkReply inside it)
void QuoteManager::handleReply()
{
    if(m_reply->error() == QNetworkReply::NoError) {
        QByteArray data = m_reply->readAll();

        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &parseError);

        if(parseError.error != QJsonParseError::NoError) {
            qWarning() << "Model JSON parse error: " << parseError.errorString();
            return;
        }

        QJsonObject rootObject = jsonDocument.object();

        QString content = rootObject["content"].toString();

        if(!content.isEmpty()) {
            setQuote(content.trimmed());
            emit quoteChanged();
            qDebug() << content;
        }

    } else
        qWarning() << "Error on LM request: " << m_reply->errorString();

    m_reply->deleteLater();
    m_reply = nullptr;
}
