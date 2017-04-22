/**
 * @file IMsgIDMappingManager.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief General interface for #IMsgIDMapping managers
 */
#ifndef IMSGIDMAPPINGMANAGER_H
#define IMSGIDMAPPINGMANAGER_H

#include "IMsgMappingManager.h"
#include "MsgIDType.h"

/**
 * @brief The IMsgIDMappingManager interface
 */
class IMsgIDMappingManager : public IMsgMappingManager
{
public:
    virtual ~IMsgIDMappingManager(){}

    virtual MsgIDType getMsgIDToAlias(const QString &alias) const = 0;
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToAlias(const QString &alias) const = 0;
};

#endif /* IMSGIDMAPPINGMANAGER_H */
