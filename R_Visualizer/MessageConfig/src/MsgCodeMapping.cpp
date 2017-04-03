#include "MsgCodeMapping.h"

#include "IMsgCodeMappingStore.h"

MsgCodeMapping::MsgCodeMapping(IMsgCodeMappingStore *msgCodeMappingStore) :
    msgCodeMappingStore(msgCodeMappingStore)
{
}

MsgCodeMapping::~MsgCodeMapping()
{
}

MsgCodeType MsgCodeMapping::getMsgCodeToAlias(const QString &alias) const
{
}

QString MsgCodeMapping::getAliasToMsgCode(const MsgCodeType &msgCode) const
{
}

QColor MsgCodeMapping::getColorToMsgCode(const MsgCodeType &msgCode) const
{
}

QColor MsgCodeMapping::getColorToAlias(const QString &alias) const
{
}


IPrettyMsgUniqPtr<IMsg> MsgCodeMapping::prettifyMsg(
       IPrettyMsgUniqPtr<IMsg> msgToPrettify
       ) const
{
    //ToDO
    msgToPrettify->setMsgCodePlainTextAlias("SomeCodeALias");
    msgToPrettify->setMsgCodeColorRepresentation(QColor(Qt::green));
    return std::move(msgToPrettify);
}

IPrettyMsgUniqPtr<ITimestampedMsg> MsgCodeMapping::prettifyMsg(
       IPrettyMsgUniqPtr<ITimestampedMsg> msgToPrettify
       ) const
{
    //ToDO
    msgToPrettify->setMsgCodePlainTextAlias("SomeTimestampCodeLias");
    msgToPrettify->setMsgCodeColorRepresentation(QColor(Qt::green).darker());
    return std::move(msgToPrettify);
}

/* QCompleter *createCodeNameCompleter( */
/*         QObject *parent = Q_NULLPTR */
/*         ) const */
/* { */
/* } */

void MsgCodeMapping::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
