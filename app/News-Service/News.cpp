#include "News.h"

News::News(QObject *parent)
    : QObject{parent}
{}

QString News::title() const
{
    return m_title;
}

void News::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

QString News::desc() const
{
    return m_desc;
}

void News::setDesc(const QString &newDesc)
{
    if (m_desc == newDesc)
        return;
    m_desc = newDesc;
    emit descChanged();
}

QUrl News::image() const
{
    return m_image;
}

void News::setImage(const QUrl &newImage)
{
    if (m_image == newImage)
        return;
    m_image = newImage;
    emit imageChanged();
}

QString News::dateTime() const
{
    return m_dateTime;
}

void News::setDateTime(const QString &newDateTime)
{
    if (m_dateTime == newDateTime)
        return;
    m_dateTime = newDateTime;
    emit dateTimeChanged();
}

QString News::source() const
{
    return m_source;
}

void News::setSource(const QString &newSource)
{
    if (m_source == newSource)
        return;
    m_source = newSource;
    emit sourceChanged();
}
