/**
 * \file IMsgCodeMappingModel.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for storing message code mappings
 */
#ifndef IMSGCODEMODEL_H
#define IMSGCODEMODEL_H

#include <QString>
#include <QColor>
#include <QCompleter>

#include "Msg.h"
#include "IMsgCodeMapping.h"

/**
 * \brief The IMsgCodeMappingModel interface
 */
class IMsgCodeMappingModel : public IFileParsable
{
public:
    virtual ~IMsgCodeMappingModel(){}

    virtual IMsgCodeMapping &getMsgCodeMappingToMsgCode(
            const MsgCodeType &msgCode
            ) = 0;

    virtual bool contains(const MsgCodeType &code) const = 0;
    virtual bool contains(const IMsgCodeMapping &msgIDMapping) const = 0;

    virtual void appendMsgCodeMapping(
            const IMsgCodeMapping &msgCodeMappingToAppend
            ) = 0;
    virtual void removeMsgCodeMapping(
            const MsgCodeType &relatedCode
            ) = 0;

    virtual void clear() = 0;

    /* virtual QCompleter *createCodeNameCompleter(
     * QObject *parent = Q_NULLPTR
     * ) const = 0; */

};

#endif /* IMSGCODEMODEL_H */
