/**
 * \file ITimestampedMsg.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief This interface extends the #IMsg interface to include a timestamp
 */
#ifndef ITIMESTAMPEDMSG_H
#define ITIMESTAMPEDMSG_H


#include "IMsg.h"
#include "ITimestamp.h"

/**
 * @addtogroup TimestampGroup
 * 
 * @{
 */

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

/**
 * @}
 */

#endif /* ITIMESTAMPEDMSG_H */
