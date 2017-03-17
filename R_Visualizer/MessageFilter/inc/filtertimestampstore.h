#ifndef FILTERTIMESTAMPSTORE_H
#define FILTERTIMESTAMPSTORE_H

#include <QObject>
#include <QDateTime>

class FileParser;

#include "IFileParsable.h"

class FilterTimestampStore : public QObject, public IFileParsable
{
    Q_OBJECT
public:
    explicit FilterTimestampStore(QObject *parent = 0);

    bool isValidTimestampFrom(const QDateTime &timestamp) const;
    bool isValidTimestampTo(const QDateTime &timestamp) const;

    QDateTime getTimestampFilterFrom() const;
    void setTimestampFilterFrom(const QDateTime &value);

    QDateTime getTimestampFilterTo() const;
    void setTimestampFilterTo(const QDateTime &value);

    void accept(FileParser *visitor);

private:
    QDateTime timestampFilterFrom;
    QDateTime timestampFilterTo;
signals:
    void internalModelChanged();
public slots:
    void timestampFromChanged(const QDateTime &dateTime);
    void timestampToChanged(const QDateTime &dateTime);
};

#endif // FILTERTIMESTAMPSTORE_H
