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

    emit sgnl_MsgCodeAboutToBeAdded(msgCodeToAdd);
    msgCodeVector.append(msgCodeToAdd);
    emit sgnl_MsgCodeAdded(msgCodeToAdd);
}

void MsgCodeFilterStore::removeMsgCode(const MsgCodeType &msgCodeToRemove)
{
    if(!msgCodeVector.contains(msgCodeToRemove))
    {
        qDebug() << "MsgCodeStore does not contain: "
            << static_cast<QString>(msgCodeToRemove);
        return;
    }

    emit sgnl_MsgCodeAboutToBeRemoved(msgCodeToRemove);
    msgCodeVector.removeOne(msgCodeToRemove);
    emit sgnl_MsgCodeRemoved(msgCodeToRemove);
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

int MsgCodeFilterStore::indexOf(const MsgCodeType &msgCode) const
{
    return msgCodeVector.indexOf(msgCode);
}

void MsgCodeFilterStore::clear()
{
    emit sgnl_AboutToBeCleared();
    msgCodeVector.clear();
    emit sgnl_Cleared();
}
