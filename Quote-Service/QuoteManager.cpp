#include "QuoteManager.h"

QuoteManager::QuoteManager(QObject *parent)
    : QObject{parent}
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &QuoteManager::handleReply);

    m_request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Some models incorporate their thinking into the answer, to remove it a regex is used.
    m_thinkTag = QRegularExpression("<think>[\\s\\S]*?</think>");
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

QRegularExpression QuoteManager::thinkTag() const
{
    return m_thinkTag;
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
    payload["messages"] = messages;
    payload["temperature"] = 0.7;
    payload["max_tokens"] = 300;

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    m_manager->post(*m_request, data);
}

void QuoteManager::handleReply(QNetworkReply *reply)
{
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
        QString answer = message["content"].toString();

        if(answer.isEmpty())
            return;

        answer.remove(thinkTag());

        setQuote(answer.trimmed());

    } else
        qWarning() << "Error on LM request: " << reply->errorString();

    reply->deleteLater();
    reply = nullptr;
}
