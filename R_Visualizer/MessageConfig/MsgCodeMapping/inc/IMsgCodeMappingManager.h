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

/**
 * @brief The IMsgCodeMappingManager interface
 */
class IMsgCodeMappingManager : public IMsgMappingManager
{
public:
    virtual ~IMsgCodeMappingManager(){}

    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const = 0;
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const = 0;
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const = 0;
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    /* virtual QCompleter *createCodeAliasCompleter( */
    /*         QObject *parent = Q_NULLPTR */
    /*         ) const = 0; */
};

#endif /* IMSGCODEMAPPINGMANAGER_H */
