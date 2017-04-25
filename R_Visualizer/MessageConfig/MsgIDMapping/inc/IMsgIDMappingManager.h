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

class IMsgIDMapping;

/**
 * @brief The IMsgIDMappingManager interface
 */
class IMsgIDMappingManager : public IMsgMappingManager
{
    Q_OBJECT
public:
    virtual ~IMsgIDMappingManager(){}

    virtual MsgIDType getMsgIDToAlias(const QString &alias) const = 0;
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    virtual void addMsgIDMapping(
            const IMsgIDMapping &msgIDMapping
            ) = 0;

    virtual void removeMsgIDMapping(
            const MsgIDType &relatedMsgID
            ) = 0;
signals:

public slots:
    virtual void slt_addMsgIDMapping(const IMsgIDMapping &msgMapping)
    {
        addMsgIDMapping(msgMapping);
    }

    virtual void slt_removeMsgIDMapping(
            const MsgIDType &relatedMsgID
            )
    {
        removeMsgIDMapping(relatedMsgID);
    }

};

#endif /* IMSGIDMAPPINGMANAGER_H */
