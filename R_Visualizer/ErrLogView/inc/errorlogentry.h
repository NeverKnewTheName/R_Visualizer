/**
 * @file    errorlogentry.h
 * @author  Christian Neuberger
 * @date 2016-03-20
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

class FileParser;

#include "IFileParsable.h"

/**
 * \brief The ErrorLogEntry
 */
class ErrorLogEntry : public IFileParsable
{
public:
    ErrorLogEntry();
    ErrorLogEntry(QDateTime timestamp, QString detailString);
    ~ErrorLogEntry();

    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime &value);

    QString getDetailString() const;
    void setDetailString(const QString &value);

    void accept(FileParser *visitor);

private:
    QDateTime timestamp;
    QString detailString;
};

Q_DECLARE_METATYPE(ErrorLogEntry)

#endif // ERRORLOGENTRY_H
