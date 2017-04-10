/**
 * @file MessageStream.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The MessageStream module
 */
#ifndef MESSAGESTREAM_H
#define MESSAGESTREAM_H

#include <QObject>

#include "IMessageStream.h"

/**
 * @brief The MessageStream
 */
class MessageStream : public QObject, public IMessageStream
{
    Q_OBJECT
public:
    explicit MessageStream(QObject *parent = 0);

signals:

public slots:
};

#endif // MESSAGESTREAM_H
