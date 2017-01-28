/**
 * @file	errorlogentry.h
 * @author	Christian Neuberger
 *
 * \brief Represents one entry of the error log.
 *
 *
 *
 */

#ifndef ERRORLOGENTRY_H
#define ERRORLOGENTRY_H

#include <QString>
#include <QDateTime>

#include <QMetaType>

class ErrorLogEntry
{
public:
    ErrorLogEntry();
    ErrorLogEntry(QDateTime timestamp, QString detailString);
    ~ErrorLogEntry();

    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime &value);

    QString getDetailString() const;
    void setDetailString(const QString &value);

private:
    QDateTime timestamp;
    QString detailString;
};

Q_DECLARE_METATYPE(ErrorLogEntry)

#endif // ERRORLOGENTRY_H
