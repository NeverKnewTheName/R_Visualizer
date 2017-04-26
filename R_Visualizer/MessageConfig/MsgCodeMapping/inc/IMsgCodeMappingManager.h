/**
 * @file IMsgCodeMappingManager.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief Interface for Message Code Mapping Managers
 */
#ifndef IMSGCODEMAPPINGMANAGER_H
#define IMSGCODEMAPPINGMANAGER_H

#include "IMsgMappingManager.h"
#include "MsgCodeType.h"

class IMsgCodeMapping;

/**
 * @defgroup MsgCodeMappingGroup Message Code Mapping
 * @ingroup MsgMappingGroup
 * 
 * Every class that is related to the Message Code Mapping
 * 
 * @{
 */

/**
 * @brief The IMsgCodeMappingManager interface
 */
class IMsgCodeMappingManager : public IMsgMappingManager
{
    Q_OBJECT
public:
    IMsgCodeMappingManager(
            QObject *parent = Q_NULLPTR
            ) :
        IMsgMappingManager(parent)
    {}
    virtual ~IMsgCodeMappingManager(){}

    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const = 0;
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const = 0;
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const = 0;
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    virtual void addMsgCodeMapping(
            const IMsgCodeMapping &msgCodeMapping
            ) = 0;

    virtual void removeMsgCodeMapping(
            const MsgCodeType &relatedMsgCode
            ) = 0;
signals:

public slots:
    virtual void slt_addMsgCodeMapping(const IMsgCodeMapping &msgMapping)
    {
        addMsgCodeMapping(msgMapping);
    }

    virtual void slt_removeMsgCodeMapping(
            const MsgCodeType &relatedMsgCode
            )
    {
        removeMsgCodeMapping(relatedMsgCode);
    }

};

/**
 * @}
 */

#endif /* IMSGCODEMAPPINGMANAGER_H */
