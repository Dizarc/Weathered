#ifndef NEWS_H
#define NEWS_H

#include <QObject>
#include <QUrl>

class News : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL);
    Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY descChanged FINAL);
    Q_PROPERTY(QString dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged FINAL);
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged FINAL);

public:
    explicit News(QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);

    QString desc() const;
    void setDesc(const QString &newDesc);

    QString dateTime() const;
    void setDateTime(const QString &newDateTime);

    QString source() const;
    void setSource(const QString &newSource);

signals:
    void titleChanged();
    void descChanged();

    void dateTimeChanged();

    void sourceChanged();

private:
    QString m_title;
    QString m_desc;
    QString m_dateTime;
    QString m_source;
};

#endif // NEWS_H
