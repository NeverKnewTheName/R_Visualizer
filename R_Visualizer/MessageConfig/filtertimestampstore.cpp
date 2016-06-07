#include "filtertimestampstore.h"
#include <QDebug>

FilterTimestampStore::FilterTimestampStore(QObject *parent) : QObject(parent)
{

}

bool FilterTimestampStore::isValidTimestampFrom(QDateTime &timestamp) const
{
    return timestamp >= timestampFilterFrom;
}

bool FilterTimestampStore::isValidTimestampTo(QDateTime &timestamp) const
{
    return timestamp <= timestampFilterTo;
}

QDateTime FilterTimestampStore::getTimestampFilterFrom() const
{
    return timestampFilterFrom;
}

void FilterTimestampStore::setTimestampFilterFrom(const QDateTime &value)
{
    timestampFilterFrom = value;
}

QDateTime FilterTimestampStore::getTimestampFilterTo() const
{
    return timestampFilterTo;
}

void FilterTimestampStore::setTimestampFilterTo(const QDateTime &value)
{
    timestampFilterTo = value;
}

void FilterTimestampStore::timestampFromChanged(QDateTime dateTime)
{
    this->timestampFilterFrom = dateTime;
    emit internalModelChanged();
}

void FilterTimestampStore::timestampToChanged(QDateTime dateTime)
{
    this->timestampFilterTo = dateTime;
    emit internalModelChanged();
}
