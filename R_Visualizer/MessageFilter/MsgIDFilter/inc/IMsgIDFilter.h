/**
 * @file IMsgIDFilter.h
 * @author Christian Neuberger
 * @date 2017-04-26
 * 
 * @brief Interface for Message ID Filters
 */
#ifndef IMSGIDFILTER_H
#define IMSGIDFILTER_H

#include "IMsgFilter.h"
#include "MsgIDType.h"

/**
 * @defgroup MsgIDFilterGroup Message ID Filter
 * @ingroup MsgFieldFilterGroup
 * 
 * @{
 */

/**
 * @brief The IMsgIDFilter interface
 */
class IMsgIDFilter : public IMsgFilter
{
    Q_OBJECT
public:
    IMsgIDFilter(QObject *parent = Q_NULLPTR) :
        IMsgFilter(parent)
    {}

    virtual ~IMsgIDFilter(){}

    virtual void addMsgIDToFilter(
            const MsgIDType &msgIDToAdd
            ) = 0;

    virtual void removeMsgIDFromFilter(
            const MsgIDType &msgIDToRemove
            ) = 0;

    virtual void clear() = 0;

public slots:
    virtual void slt_addMsgIDToFilter(const MsgIDType &msgIDToAdd)
    {
        addMsgIDToFilter(msgIDToAdd);
    }

    virtual void slt_removeMsgIDFromFilter(const MsgIDType &msgIDToRemove)
    {
        removeMsgIDFromFilter(msgIDToRemove);
    }

};

/**
 * @}
 */
#endif /* IMSGIDFILTER_H */
