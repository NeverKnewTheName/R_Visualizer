#include "MsgCodeFilterStore.h"

#include <QString>
#include <QDebug>

MsgCodeFilterStore::MsgCodeFilterStore()
{
}

MsgCodeFilterStore::~MsgCodeFilterStore()
{
}

void MsgCodeFilterStore::addMsgCode(const MsgCodeType &msgCodeToAdd)
{
    if(msgCodeVector.contains(msgCodetoAdd))
    {
        qDebug() << "MsgCodeStore does already contain: "
            << static_cast<QString>(msgCodeToAdd);
        return;
    }

    msgCodeVector.append(msgCodeToAdd);
}

void MsgCodeFilterStore::removeMsgCode(const MsgCodeType &msgCodeToRemove)
{
    if(!msgCodeVector.contains(msgCodetoAdd))
    {
        qDebug() << "MsgCodeStore does not contain: "
            << static_cast<QString>(msgCodeToAdd);
        return;
    }

    msgCodeVector.removeOne(msgCodeToRemove);
}

MsgCodeFilterStore::containsMsgCode(const MsgCodeType &msgCode) const
{
    return msgCodeVector.contains(msgCode);
}

MsgCodeFilterStore::clear()
{
    msgCodeVector.clear();
}

