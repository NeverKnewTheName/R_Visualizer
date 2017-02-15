#ifndef FILTERTIMESTAMPSTORE_H
#define FILTERTIMESTAMPSTORE_H

#include <QObject>
#include <QDateTime>

class FileParser;

#include "fileparsable.h"

class FilterTimestampStore : public QObject, public FileParsable
{
    Q_OBJECT
public:
    explicit FilterTimestampStore(QObject *parent = 0);

    bool isValidTimestampFrom(QDateTime &timestamp) const;
    bool isValidTimestampTo(QDateTime &timestamp) const;

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
    void timestampFromChanged(QDateTime dateTime);
    void timestampToChanged(QDateTime dateTime);
};

#endif // FILTERTIMESTAMPSTORE_H
