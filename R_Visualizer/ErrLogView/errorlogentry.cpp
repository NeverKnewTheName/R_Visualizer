#include "errorlogentry.h"

ErrorLogEntry::ErrorLogEntry() :
    timestamp(QDateTime()),
    rxErrCntr(0),
    txErrCntr(0),
    detailString(QString())
{

}

ErrorLogEntry::ErrorLogEntry(QDateTime timestamp, int rxErrCntr, int txErrCntr, QString detailString) :
    timestamp(timestamp),
    rxErrCntr(rxErrCntr),
    txErrCntr(txErrCntr),
    detailString(detailString)
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

int ErrorLogEntry::getRxErrCntr() const
{
    return rxErrCntr;
}

void ErrorLogEntry::setRxErrCntr(int value)
{
    rxErrCntr = value;
}

int ErrorLogEntry::getTxErrCntr() const
{
    return txErrCntr;
}

void ErrorLogEntry::setTxErrCntr(int value)
{
    txErrCntr = value;
}

QString ErrorLogEntry::getDetailString() const
{
    return detailString;
}

void ErrorLogEntry::setDetailString(const QString &value)
{
    detailString = value;
}
