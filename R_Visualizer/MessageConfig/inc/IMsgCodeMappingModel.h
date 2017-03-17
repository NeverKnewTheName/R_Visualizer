#ifndef IMSGCODEMODEL_H
#define IMSGCODEMODEL_H

#include <QString>
#include <QColor>
#include <QCompleter>

#include "msg.h"
#include "IMsgCodeRep.h"

class IMsgCodeMappingModel
{
public:
    IMsgCodeMappingModel();
    virtual ~IMsgCodeMappingModel();

    IMsgCodeRep getMsgCodeRepToCode(const MsgCodeType code) const = 0;
    QString getNameToCode(const MsgCodeType code) const = 0;
    MsgCodeType getCodeToName(const QString &name) const = 0;
    QColor getColorToCode(const MsgCodeType code) const = 0;

    bool contains(const MsgCodeType code) const = 0;

    QCompleter *createCodeNameCompleter(QObject *parent = Q_NULLPTR) const = 0;

signals:
    sgnl_MsgCodeRepAdded(const IMsgCodeRep &newMsgCodeRep) = 0;
    sgnl_MsgCodeRepUpdated(const IMsgCodeRep &updatedMsgCodeRep) = 0;
    sgnl_MsgCodeRepRemoved(const MsgCodeType relatedCode) = 0;
};

#endif /* IMSGCODEMODEL_H */
