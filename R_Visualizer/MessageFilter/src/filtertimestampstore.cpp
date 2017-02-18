#include "filtertimestampstore.h"
#include <QDebug>

#include "fileparser.h"

FilterTimestampStore::FilterTimestampStore(QObject *parent) : QObject(parent)
{

}

bool FilterTimestampStore::isValidTimestampFrom(const QDateTime &timestamp) const
{
    return timestamp >= timestampFilterFrom;
}

bool FilterTimestampStore::isValidTimestampTo(const QDateTime &timestamp) const
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

void FilterTimestampStore::timestampFromChanged(const QDateTime &dateTime)
{
    this->timestampFilterFrom = dateTime;
    emit internalModelChanged();
}

void FilterTimestampStore::timestampToChanged(const QDateTime &dateTime)
{
    this->timestampFilterTo = dateTime;
    emit internalModelChanged();
}

void FilterTimestampStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
