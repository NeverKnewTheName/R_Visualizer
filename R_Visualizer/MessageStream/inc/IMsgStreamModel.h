/**
 * @file IMsgStreamModel.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief Provides the interface of a MessageStream model
 */
#ifndef IMSGSTREAMMODEL_H
#define IMSGSTREAMMODEL_H

#include "IMsgStreamStore.h"

/**
 * @brief The IMsgStreamModel interface
 */
class IMsgStreamModel
{
public:
    virtual ~IMsgStreamModel(){}

    /* /** */
    /*  * @brief Appends a message to the model */
    /*  *1/ */
    /* virtual void appendMsg(const ITimestampedMsg &msgToAppend) = 0; */

    /* /** */
    /*  * @brief Clears the model removing all contained messages */
    /*  *1/ */
    /* virtual void clear() = 0; */

public slots:
    /* virtual void slt_appendMsg(const ITimestampedMsg &msgToAppend) = 0; */
    /* virtual void slt_prependMsg(const ITimestampedMsg &msgToAppend) = 0; */

};

#endif /* IMSGSTREAMMODEL_H */
