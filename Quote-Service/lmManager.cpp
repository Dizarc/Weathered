#include "lmManager.h"

LmManager::LmManager(QObject *parent)
    : QObject{parent}
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &LmManager::handleReply);

    m_request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Some models incorporate their thinking into the answer, use regex to remove it.
    m_thinkTag = QRegularExpression("<think>[\\s\\S]*?</think>");

    m_dailyQuoteTimer = new QTimer(this);
    m_dailyQuoteTimer->setSingleShot(true);
    connect(m_dailyQuoteTimer, &QTimer::timeout, this, &LmManager::refreshDailyQuote);

    QDateTime now = QDateTime::currentDateTime();
    QDateTime midnight(now.date().addDays(1), QTime(0, 0, 0));
    m_dailyQuoteTimer->start(now.msecsTo(midnight));

    generateQuote();
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
    QJsonArray messages;

    messages.append(QJsonObject {
        {"role", "system"},
        {"content", "You are Qwen, a supportive assistant AI. "
                    "Your main goal is to inspire and uplift users with short motivational messages "
                    "that are simple, positive, and easy to understand. "
                    "You should also add a positive emoji at the end of the quote. "
                    "Provide nothing more than the sentences and the emoji at the end."}
    });

    messages.append(QJsonObject {
        {"role", "user"},
        {"content", "Write a short uplifting quote (no more than 2 sentences) for someone starting their day."
                    "Keep it positive, encouraging, and easy to read."}
    });

    QJsonObject payload;
    payload["messages"] = messages;
    payload["temperature"] = 0.8;
    payload["max_tokens"] = 500;

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = m_manager->post(*m_request, data);

    reply->setProperty("lm_task", static_cast<int>(Task::Quote));
}

void LmManager::generateSuggestion(const QString city, const QString desc, const QString dateTime, const double temp, const double feelTemp, const double humidity, const double wind, const double clouds)
{
    QJsonArray messages;

    messages.append(QJsonObject {
        {"role", "system"},
        {"content", "You are Qwen, a stylist assistant AI. "
                    "Your top priority is the help users choose practical and stylish outfits based on the weather. "
                    "Never suggest heavy jackets, coats, or boots during summmer unless the temperature is unexpectedly cold. "
                    "Never suggest light clothing like shorts during winter unless the weather is unusually hot."
                    "Always provide your answer in plain text only. Do NOT use bold, italics, or markdown formatting. "
                    "Format your answer in a structured, multi-line way using different labels. "
                    "Each item should be on a separate line for readability with one extra new line between them. "
                    "You should also provide clothes for Women and Men separately."}
    });

    messages.append(QJsonObject {
        {"role", "user"},
        {"content", QString("Suggest an outfit for today's weather and season:\n"
                            "City: %1\n"
                            "Description: %2\n"
                            "Date and Time: %3\n"
                            "Temperature: %4 Celcius\n"
                            "Feel temperature: %5 Celcius\n"
                            "Humidity: %6 %\n"
                            "Wind: %7 meters/seconds\n"
                            "cloudiness: %8 %\n"
                            "The outfit should be practical, comfortable, and suitable "
                            "for the current city and the date (take into consideration if its summer, winter, autumn, or spring).")
                        .arg(city)
                        .arg(desc)
                        .arg(dateTime)
                        .arg(QString::number(temp))
                        .arg(QString::number(feelTemp))
                        .arg(QString::number(humidity))
                        .arg(QString::number(wind))
                        .arg(QString::number(clouds))}
    });

    QJsonObject payload;
    payload["messages"] = messages;
    payload["temperature"] = 0.7;
    payload["max_tokens"] = 1000;

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

void LmManager::refreshDailyQuote()
{
    generateQuote();

    QDateTime now = QDateTime::currentDateTime();
    QDateTime midnight(now.date().addDays(1), QTime(0, 0, 0));
    m_dailyQuoteTimer->start(now.msecsTo(midnight));
}


