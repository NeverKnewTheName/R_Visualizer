/**
 * @file IMsgDataMappingManager.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief Interface for Message Data Mappings
 */
#ifndef IMSGDATAMAPPINGMANAGER_H
#define IMSGDATAMAPPINGMANAGER_H

#include "IMsgMappingManager.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"

class IMsgDataFormatter;
class IMsgDataMapping;
class IMsgDataMappingStore;

class IMsg;

/**
 * @defgroup MsgDataMappingGroup Message Data Mapping
 * @ingroup MsgMappingGroup
 * 
 * Every class that is related to the Message Data Mapping
 * 
 * @{
 */


/**
 * @brief The IMsgDataMappingManager interface
 */
class IMsgDataMappingManager : public IMsgMappingManager
{
    Q_OBJECT
public:
    IMsgDataMappingManager(
            QObject *parent = Q_NULLPTR
            ) :
        IMsgMappingManager(parent)
    {}
    virtual ~IMsgDataMappingManager(){}

    virtual QString parseMsgDataToString(const IMsg &msg) const = 0;
    virtual QColor parseMsgDataToColor(const IMsg &msg) const = 0;

    virtual IMsgDataFormatter *getMsgDataFormatter(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const = 0;

    virtual QString getMsgDataFormatString(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const = 0;

    virtual void addMsgDataMapping(
            const IMsgDataMapping &msgDataMapping
            ) = 0;

    virtual void removeMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) = 0;

    virtual IMsgDataMappingStore *getStore() const = 0;

signals:
    void sgnl_MsgDataMappingManagerChanged(const IMsgDataMappingManager &changedMappingManager);

public slots:

    /**
     * @brief Slot adds the specified #IMsgDataMapping
     * 
     * @note Calls #addMsgDataMapping
     */
    void slt_AddMsgDataMapping(
            const IMsgDataMapping &msgDataMappingToAdd
            )
    {
        addMsgDataMapping(msgDataMappingToAdd);
    }

    /**
     * @brief Slot removes the #IMsgDataMapping related to the specified
     * #MsgIDType and #MsgCodeType
     * 
     * @note Calls #removeMsgDataMapping
     */
    void slt_RemoveMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            )
    {
        removeMsgDataMapping(msgID, msgCode);
    }


};

/**
 * @}
 */

#endif /* IMSGDATAMAPPINGMANAGER_H */
