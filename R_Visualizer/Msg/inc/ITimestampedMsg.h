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

template<class Derived>
class AbstractTimestampedMsgCRTPHelper : public ITimestampedMsg
{
public:
    virtual IMsg *cloneMsg() const
    {
        return new Derived(static_cast<const Derived&>(*this));
    }
    virtual void accept(FileParser *visitor)
    {
        visitor->visit(static_cast<Derived *>(this));
    }
};

#endif /* ITIMESTAMPEDMSG_H */
