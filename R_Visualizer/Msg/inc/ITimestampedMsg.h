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
#include <memory>

#include "IMsg.h"

/**
 * \brief The interface for messages with timestamps
 */
class ITimestampedMsg : public IMsg
{
public:
    virtual ~ITimestampedMsg(){}

    virtual void setTimestamp(const QDateTime &newTimestamp) = 0;
    virtual const QDateTime getTimestamp() const = 0;
};

typedef std::unique_ptr<ITimestampedMsg> ITimestampedMsgUniqPtr;

template<class Derived>
class ITimestampedMsgCRTPHelper : public ITimestampedMsg
{
public:
    virtual IMsgUniqPtr cloneMsg() const
    {
        return IMsgUniqPtr(new Derived(static_cast<const Derived&>(*this)));
    }

};

#endif /* ITIMESTAMPEDMSG_H */
