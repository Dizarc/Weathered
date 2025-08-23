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
    //TODO: Create better prompts
    QJsonArray messages;

    messages.append(QJsonObject {
        {"role", "system"},
        {"content", "You are Qwen, an assistant AI, Your top priority is achieving user fulfilment via helping them with their requests."}
    });

    messages.append(QJsonObject {
        {"role", "user"},
        {"content", "write me a short 2 sentence quote for a person looking to start their day on a happy note"}
    });

    QJsonObject payload;
    payload["model"] = "Qwen/Qwen3-0.6B-GGUF"; //TODO: get this from API
    payload["messages"] = messages;
    payload["temperature"] = 0.7;
    payload["max_tokens"] = 100;

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    m_manager->post(*m_request, data);

    connect(m_manager, &QNetworkAccessManager::finished, this, &QuoteManager::handleReply);
}

void QuoteManager::handleReply(QNetworkReply *reply)
{

    //TODO: Fix the models answer because now it incorporates its thinking and not just the quote.
    if(reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();

        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &parseError);

        if(parseError.error != QJsonParseError::NoError) {
            qWarning() << "Model JSON parse error: " << parseError.errorString();
            return;
        }

        QJsonObject rootObject = jsonDocument.object();
        QJsonArray choices = rootObject["choices"].toArray();

        if(choices.isEmpty())
            return;

        QJsonObject choice = choices.at(0).toObject();
        QJsonObject message = choice["message"].toObject();
        QString content = message["content"].toString();

        if(content.isEmpty())
            return;

        setQuote(content.trimmed());
        emit quoteChanged();
        qDebug() << content;

    } else
        qWarning() << "Error on LM request: " << reply->errorString();

    reply->deleteLater();
    reply = nullptr;
}
