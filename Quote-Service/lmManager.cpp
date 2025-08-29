#include "lmManager.h"

LmManager::LmManager(QObject *parent)
    : QObject{parent}
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &LmManager::handleReply);

    m_request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Some models incorporate their thinking into the answer, to remove it a regex is used.
    m_thinkTag = QRegularExpression("<think>[\\s\\S]*?</think>");
}

QRegularExpression LmManager::thinkTag() const
{
    return m_thinkTag;
}

QString LmManager::quote() const
{
    return m_quote;
}

void LmManager::setQuote(const QString &newQuote)
{
    if (m_quote == newQuote)
        return;
    m_quote = newQuote;
    emit quoteChanged();
}

QString LmManager::suggestion() const
{
    return m_suggestion;
}

void LmManager::setSuggestion(const QString &newSuggestion)
{
    if (m_suggestion == newSuggestion)
        return;
    m_suggestion = newSuggestion;
    emit suggestionChanged();
}

void LmManager::generateQuote()
{
    //TODO: Create better prompts for quotes
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
    payload["temperature"] = 0.6;
    payload["max_tokens"] = 300;

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = m_manager->post(*m_request, data);

    reply->setProperty("lm_task", static_cast<int>(Task::Quote));
}

void LmManager::generateSuggestion(const QString desc, const double temp, const double feelTemp, const double humidity, const double wind, const double clouds)
{
    //TODO: Create better prompts for Suggesting clothes + Add city and day variables to take seasons into consideration.
    QJsonArray messages;

    messages.append(QJsonObject {
        {"role", "system"},
        {"content", "You are Qwen, a stylist assistant AI, "
                    "Your top priority is achieving user fulfilment via helping users pick out their outfits depending different weather variables."}
    });

    messages.append(QJsonObject {
        {"role", "user"},
        {"content", QString("Help me pick out an outfit for the Weather with:\n"
                            "Description: %1\n"
                            "Temperature: %2 Celcius\n"
                            "Feel temperature: %3 Celcius\n"
                            "Humidity: %4 %\n"
                            "Wind: %5 meters/seconds\n"
                            "cloudiness: %6 %")
                        .arg(desc)
                        .arg(QString::number(temp))
                        .arg(QString::number(feelTemp))
                        .arg(QString::number(humidity))
                        .arg(QString::number(wind))
                        .arg(QString::number(clouds))}
    });

    QJsonObject payload;
    payload["messages"] = messages;
    payload["temperature"] = 0.8;
    payload["max_tokens"] = 500;

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = m_manager->post(*m_request, data);

    reply->setProperty("lm_task", static_cast<int>(Task::Suggestion));
}

void LmManager::handleReply(QNetworkReply *reply)
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
        answer = answer.trimmed();

        int lmUse = reply->property("lm_task").toInt();
        if(lmUse == Task::Quote)
            setQuote(answer);
        else if(lmUse == Task::Suggestion)
            setSuggestion(answer);

    } else
        qWarning() << "Error on LM request: " << reply->errorString();

    reply->deleteLater();
    reply = nullptr;
}


