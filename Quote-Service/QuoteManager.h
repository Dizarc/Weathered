#ifndef QUOTEMANAGER_H
#define QUOTEMANAGER_H

#include <QObject>

class QuoteManager : public QObject
{
    Q_OBJECT
public:
    explicit QuoteManager(QObject *parent = nullptr);

signals:
};

#endif // QUOTEMANAGER_H
