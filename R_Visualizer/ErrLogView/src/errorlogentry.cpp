#include "errorlogentry.h"

#include "fileparser.h"

ErrorLogEntry::ErrorLogEntry() :
    timestamp(QDateTime()),
    detailString(QString())
{

}

ErrorLogEntry::ErrorLogEntry(QDateTime timestamp, QString detailString) :
    timestamp(timestamp),
    detailString(detailString)
{

}

ErrorLogEntry::~ErrorLogEntry()
{

}

QDateTime ErrorLogEntry::getTimestamp() const
{
    return timestamp;
}

void ErrorLogEntry::setTimestamp(const QDateTime &value)
{
    timestamp = value;
}

QString ErrorLogEntry::getDetailString() const
{
    return detailString;
}

void ErrorLogEntry::setDetailString(const QString &value)
{
    detailString = value;
}

void ErrorLogEntry::accept(FileParser *visitor)
{
    //ToDo
    //visitor->visit(*this);
}
