/**
 * \file ITimestampedMsg.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief This interface extends the #IMsg interface to include a timestamp
 */
#ifndef ITIMESTAMPEDMSG_H
#define ITIMESTAMPEDMSG_H

#include <QDateTime>

#include "IMsg.h"

/**
 * @brief The ITimestamp interface provides methods to organize a timestamp
 */
class ITimestamp
{
public:
    virtual ~ITimestamp(){}

    virtual void setTimestamp(const QDateTime &newTimestamp) = 0;
    virtual const QDateTime getTimestamp() const = 0;
};

/**
 * \brief The interface for messages with timestamps
 * 
 * This interface groups #IMsg and #ITimestamp into one #ITimestampedMsg
 * interface. This allows for messages to include a timestamp.
 * 
 * \note #ITimestampedMsg are usable as #IMsg
 */
class ITimestampedMsg : public IMsg, public ITimestamp
{
public:
    virtual ~ITimestampedMsg(){}
};

#endif /* ITIMESTAMPEDMSG_H */
