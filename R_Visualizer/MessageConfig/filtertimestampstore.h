#ifndef FILTERTIMESTAMPSTORE_H
#define FILTERTIMESTAMPSTORE_H

#include <QObject>

class FilterTimestampStore : public QObject
{
    Q_OBJECT
public:
    explicit FilterTimestampStore(QObject *parent = 0);

signals:

public slots:
};

#endif // FILTERTIMESTAMPSTORE_H