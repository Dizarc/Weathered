#ifndef LMMANAGER_H
#define LMMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <QRegularExpression>
#include <QTimer>

#include "Weather-Service/ApiAccess.hpp"

class LmManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString quote READ quote WRITE setQuote NOTIFY quoteChanged FINAL)
    Q_PROPERTY(QString suggestion READ suggestion WRITE setSuggestion NOTIFY suggestionChanged FINAL)

public:
    explicit LmManager(QObject *parent = nullptr);

    QRegularExpression thinkTag() const;

    QString quote() const;
    void setQuote(const QString &newQuote);

    QString suggestion() const;
    void setSuggestion(const QString &newSuggestion);

public slots:
    void generateQuote();
    void generateSuggestion(const QString city,
                            const QString desc,
                            const QString dateTime,
                            const double temp,
                            const double feelTemp,
                            const double humidity,
                            const double wind,
                            const double clouds);

private slots:
    void handleReply(QNetworkReply *reply);

    void  refreshDailyQuote();

signals:
    void quoteChanged();

    void suggestionChanged();

private:
    QNetworkAccessManager *m_manager;
    QNetworkRequest *m_request = new QNetworkRequest(ModelAPI::LM_URL);

    QRegularExpression m_thinkTag;

    QTimer *m_dailyQuoteTimer;

    QString m_quote;
    QString m_suggestion;
    // For setting different Q properties depending on the task needed
    enum Task {
        Quote,
        Suggestion
    };

};

#endif // LMMANAGER_H
