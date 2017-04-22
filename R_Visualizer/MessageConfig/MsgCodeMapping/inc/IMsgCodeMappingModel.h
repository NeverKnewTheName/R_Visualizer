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
class IMsgCodeMappingModel
{
public:
    IMsgCodeMappingModel();
    virtual ~IMsgCodeMappingModel();

    //IMsgCodeMapping getMsgCodeMappingToCode(const MsgCodeType code) const = 0;
    virtual QString getNameToCode(const MsgCodeType code) const = 0;
    virtual MsgCodeType getCodeToName(const QString &name) const = 0;
    virtual QColor getColorToCode(const MsgCodeType code) const = 0;

    virtual bool contains(const MsgCodeType code) const = 0;

    virtual QCompleter *createCodeNameCompleter(QObject *parent = Q_NULLPTR) const = 0;

signals:
    virtual void sgnl_MsgCodeMappingAdded(const IMsgCodeMapping &newMsgCodeMapping) = 0;
    virtual void sgnl_MsgCodeMappingUpdated(const IMsgCodeMapping &updatedMsgCodeMapping) = 0;
    virtual void sgnl_MsgCodeMappingRemoved(const MsgCodeType relatedCode) = 0;
};

#endif /* IMSGCODEMODEL_H */
