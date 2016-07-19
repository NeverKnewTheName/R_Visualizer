#ifndef ERRORLOGENTRY_H
#define ERRORLOGENTRY_H

#include <QString>
#include <QDateTime>

class ErrorLogEntry
{
public:
    ErrorLogEntry();
    ErrorLogEntry(QDateTime timestamp, int rxErrCntr, int txErrCntr, QString detailString);

    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime &value);

    int getRxErrCntr() const;
    void setRxErrCntr(int value);

    int getTxErrCntr() const;
    void setTxErrCntr(int value);

    QString getDetailString() const;
    void setDetailString(const QString &value);

private:
    QDateTime timestamp;
    int rxErrCntr;
    int txErrCntr;
    QString detailString;
};

#endif // ERRORLOGENTRY_H
