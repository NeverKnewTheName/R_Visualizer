/**
 * @file IMsgCodeFilter.h
 * @author Christian Neuberger
 * @date 2017-04-26
 * 
 * @brief Interface for Message Code Filters
 */
#ifndef IMSGCODEFILTER_H
#define IMSGCODEFILTER_H

#include "IMsgFilter.h"

#include "MsgCodeType.h"

/**
 * @defgroup MsgCodeFilterGroup Message Code Filter
 * @ingroup MsgFieldFilterGroup
 * 
 * @{
 */

/**
 * @brief The IMsgCodeFilter interface
 */
class IMsgCodeFilter : public IMsgFilter
{
    Q_OBJECT
public:
    IMsgCodeFilter(QObject *parent = Q_NULLPTR) :
        IMsgFilter(parent)
    {}

    virtual ~IMsgCodeFilter(){}

    virtual void addMsgCodeToFilter(
            const MsgCodeType &msgCodeToAdd
            ) = 0;
    virtual void removeMsgCodeFromFilter(
            const MsgCodeType &msgCodeToRemove
            ) = 0;

public slots:
    virtual void slt_addMsgCodeToFilter(
            const MsgCodeType &msgCodeToAdd
            )
    {
        addMsgCodeToFilter(msgCodeToAdd);
    }

    virtual void slt_removeMsgCodeFromFilter(
            const MsgCodeType &msgCodeToRemove
            )
    {
        removeMsgCodeFromFilter(msgCodeToRemove);
    }

};

/**
 * @}
 */

#endif /* IMSGCODEFILTER_H */
