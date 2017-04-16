/**
 * @file IMsgCodeMapping.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief Interface for Message Code Mappings
 */
#ifndef IMSGCODEMAPPING_H
#define IMSGCODEMAPPING_H

#include "IMsgMapping.h"

#include <QCompleter>

/**
 * @brief The IMsgCodeMapping interface
 */
class IMsgCodeMapping : public IMsgMapping
{
public:
    virtual ~IMsgCodeMapping(){}

    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const = 0;
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const = 0;
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const = 0;
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    /* virtual QCompleter *createCodeAliasCompleter( */
    /*         QObject *parent = Q_NULLPTR */
    /*         ) const = 0; */
};

#endif /* IMSGCODEMAPPING_H */
