/**
 * @file MsgDataMappingManager.h
 * @author Christian Neuberger
 * @date 2017-04-22
 * 
 * @brief Manager for #IMsgDataMapping
 */
#ifndef MSGDATAMAPPINGMANAGER_H
#define MSGDATAMAPPINGMANAGER_H

#include "IMsgDataMappingManager.h"
#include "IMsgDataMappingStore.h"

class FileParser;
class IMsg;

/**
 * @addtogroup MsgDataMappingGroup
 * 
 * @{
 */

/**
 * @brief The MsgDataMappingManager
 */
class MsgDataMappingManager : public IMsgDataMappingManager
{
public:
    MsgDataMappingManager(
            IMsgDataMappingStore *msgDataMappingStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgDataMappingManager();

    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    virtual QString parseMsgDataToString(const IMsg &msg) const;
    virtual QColor parseMsgDataToColor(const IMsg &msg) const;

    virtual IMsgDataFormatter *getMsgDataFormatter(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const;

    virtual QString getMsgDataFormatString(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const;

    virtual void addMsgDataMapping(
            const IMsgDataMapping &msgDataMapping
            );

    virtual void removeMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    virtual IMsgDataMappingStore *getStore() const;

    virtual void accept(FileParser *visitor);

    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);

private:
    IMsgDataMappingStore *msgDataMappingStore;

};

/**
 * @}
 */

#endif /* MSGDATAMAPPINGMANAGER_H */
