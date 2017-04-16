/**
 * @file IMsgIDMapping.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief Interface for Message ID Mappings
 */
#ifndef IMSGIDMAPPING_H
#define IMSGIDMAPPING_H

#include "IMsgMapping.h"

/* #include <QCompleter> */

/**
 * @brief The IMsgIDMapping interface
 */
class IMsgIDMapping : public IMsgMapping
{
public:
    virtual ~IMsgIDMapping(){}

    virtual MsgIDType getMsgIDToAlias(const QString &alias) const = 0;
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    /* virtual QCompleter *createIDNameCompleter( */
    /*         QObject *parent = Q_NULLPTR */
    /*         ) const = 0; */
};

#endif /* IMSGIDMAPPING_H */
