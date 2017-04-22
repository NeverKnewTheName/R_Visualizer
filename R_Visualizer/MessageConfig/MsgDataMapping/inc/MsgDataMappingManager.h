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

/**
 * @brief The MsgDataMappingManager
 */
class MsgDataMappingManager : public IMsgDataMappingManager
{
public:
    MsgDataMappingManager(IMsgDataMappingStore *msgDataMappingStore);
    virtual ~MsgDataMappingManager();

    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    virtual void accept(FileParser *visitor);
private:
    IMsgDataMappingStore *msgDataMappingStore;


    // IUserRoleManageable interface
public:
    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);
};

#endif /* MSGDATAMAPPINGMANAGER_H */
