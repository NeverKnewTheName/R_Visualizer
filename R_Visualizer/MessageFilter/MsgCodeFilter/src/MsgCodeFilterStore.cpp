#include "MsgCodeFilterStore.h"

#include <QString>
#include <QDebug>

MsgCodeFilterStore::MsgCodeFilterStore(QObject *parent) :
    IMsgCodeFilterStore(parent)
{
}

MsgCodeFilterStore::~MsgCodeFilterStore()
{
}

void MsgCodeFilterStore::addMsgCode(const MsgCodeType &msgCodeToAdd)
{
    if(msgCodeVector.contains(msgCodeToAdd))
    {
        qDebug() << "MsgCodeStore does already contain: "
            << static_cast<QString>(msgCodeToAdd);
        return;
    }

    msgCodeVector.append(msgCodeToAdd);
}

void MsgCodeFilterStore::removeMsgCode(const MsgCodeType &msgCodeToRemove)
{
    if(!msgCodeVector.contains(msgCodeToRemove))
    {
        qDebug() << "MsgCodeStore does not contain: "
            << static_cast<QString>(msgCodeToRemove);
        return;
    }

    msgCodeVector.removeOne(msgCodeToRemove);
}

bool MsgCodeFilterStore::containsMsgCode(const MsgCodeType &msgCode) const
{
    return msgCodeVector.contains(msgCode);
}

const MsgCodeType &MsgCodeFilterStore::at(const int index) const
{
    return msgCodeVector.at(index);
}

MsgCodeType &MsgCodeFilterStore::at(const int index)
{
    return msgCodeVector[index];
}

int MsgCodeFilterStore::size() const
{
    return msgCodeVector.size();
}

void MsgCodeFilterStore::clear()
{
    msgCodeVector.clear();
}

