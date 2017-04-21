#ifndef MSGDATAMAPPING_H
#define MSGDATAMAPPING_H

#include "IMsgDataMapping.h"
#include "IMsgDataMappingStore.h"

class FileParser;

class MsgDataMapping : public IMsgDataMapping
{
public:
    MsgDataMapping(IMsgDataMappingStore *msgDataMappingStore);
    virtual ~MsgDataMapping();

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

#endif /* MSGDATAMAPPING_H */
