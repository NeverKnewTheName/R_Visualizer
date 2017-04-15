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
#include "IMsgCodeRep.h"

/**
 * \brief The IMsgCodeMappingModel interface
 */
class IMsgCodeMappingModel
{
public:
    IMsgCodeMappingModel();
    virtual ~IMsgCodeMappingModel();

    //IMsgCodeRep getMsgCodeRepToCode(const MsgCodeType code) const = 0;
    virtual QString getNameToCode(const MsgCodeType code) const = 0;
    virtual MsgCodeType getCodeToName(const QString &name) const = 0;
    virtual QColor getColorToCode(const MsgCodeType code) const = 0;

    virtual bool contains(const MsgCodeType code) const = 0;

    virtual QCompleter *createCodeNameCompleter(QObject *parent = Q_NULLPTR) const = 0;

signals:
    virtual void sgnl_MsgCodeRepAdded(const IMsgCodeRep &newMsgCodeRep) = 0;
    virtual void sgnl_MsgCodeRepUpdated(const IMsgCodeRep &updatedMsgCodeRep) = 0;
    virtual void sgnl_MsgCodeRepRemoved(const MsgCodeType relatedCode) = 0;
};

#endif /* IMSGCODEMODEL_H */
