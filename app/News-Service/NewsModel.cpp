#include "NewsModel.h"

NewsModel::NewsModel(QObject *parent) : QAbstractListModel{parent}
{
    m_manager = new QNetworkAccessManager(this);

    fetchData();
}

int NewsModel::rowCount(const QModelIndex &parent) const
{
    return m_newsList.size();
}

QVariant NewsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() <0 || index.row() >= m_newsList.size())
        return {};

    News *news = m_newsList[index.row()];

    switch(role) {
    case titleRole:
        return news->title();
    case descRole:
        return news->desc();
    case imageRole:
        return news->image();
    case dateTimeRole:
        return news->dateTime();
    case sourceRole:
        return news->source();
    default:
        return {};
    }
}

QHash<int, QByteArray> NewsModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[titleRole] = "title";
    names[descRole] = "desc";
    names[imageRole] = "image";
    names[dateTimeRole] = "dateTime";
    names[sourceRole] = "source";

    return names;
}

QList<News*> NewsModel::newsList() const
{
    return m_newsList;
}

void NewsModel::setNewsList(const QList<News*> &newNewsList)
{
    m_newsList = newNewsList;
}

void NewsModel::fetchData()
{
    if(NewsAPI::KEY.isEmpty()) {
        qWarning() << "Environmental variable \"NEWS_API_KEY\" is empty!";
        return;
    }

    if(m_reply) {
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = nullptr;
    }

    QUrlQuery query;

    query.addQueryItem("api_token", NewsAPI::KEY);
    query.addQueryItem("categories", NewsAPI::CATEGORIES);
    query.addQueryItem("language", NewsAPI::LANG);

    m_reply = m_manager->get(QNetworkRequest(NewsAPI::URL + "all?" + query.toString()));

    connect(m_reply, &QNetworkReply::finished, this, &NewsModel::parseData);
}

void NewsModel::parseData()
{
    if(m_reply->error() == QNetworkReply::NoError) {
        QByteArray data = m_reply->readAll();

        QJsonParseError parseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &parseError);

        if(parseError.error == QJsonParseError::NoError) {
            QJsonObject rootObject = jsonDocument.object();

            QJsonArray newsArray = rootObject["data"].toArray();

            QList<News*> newsList;

            for(const QJsonValue &value : newsArray) {
                QJsonObject entry = value.toObject();

                News *news = new News(this);

                news->setTitle(entry["title"].toString());
                news->setDesc(entry["description"].toString());
                news->setImage(QUrl(entry["image_url"].toString()));
                news->setDateTime(entry["published_at"].toString());
                news->setSource(entry["source"].toString());

                newsList << news;
            }

            clearList();
            addNews(newsList);
        }
        else
            qWarning() << "News JSON parse error: " << parseError.errorString();
    }
    else
        qWarning() << "Error from news API reply: " << m_reply->errorString();

    m_reply->deleteLater();
    m_reply = nullptr;
}

void NewsModel::clearList()
{
    if(m_newsList.isEmpty())
        return;

    beginResetModel();

    qDeleteAll(m_newsList);
    m_newsList.clear();

    endResetModel();
}

void NewsModel::addNews(QList<News*> &news)
{
    int start = m_newsList.length();
    int end = start + news.length() - 1;

    beginInsertRows(QModelIndex(), start, end);

    m_newsList.append(news);

    endInsertRows();
}
