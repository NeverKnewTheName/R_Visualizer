#include "MsgIDFilterStore.h"

#include <QString>
#include <QDebug>

MsgIDFilterStore::MsgIDFilterStore(QObject *parent) :
    IMsgIDFilterStore(parent)
{
}

MsgIDFilterStore::~MsgIDFilterStore()
{
}

void MsgIDFilterStore::addMsgID(const MsgIDType &msgIDToAdd)
{
    if(msgIDVector.contains(msgIDToAdd))
    {
        qDebug() << "MsgIDStore does already contain: "
            << static_cast<QString>(msgIDToAdd);
        return;
    }

    emit sgnl_MsgIDAboutToBeAdded(msgIDToAdd);
    msgIDVector.append(msgIDToAdd);
    emit sgnl_MsgIDAdded(msgIDToAdd);
}

void MsgIDFilterStore::removeMsgID(const MsgIDType &msgIDToRemove)
{
    if(!msgIDVector.contains(msgIDToRemove))
    {
        qDebug() << "MsgIDStore does not contain: "
            << static_cast<QString>(msgIDToRemove);
        return;
    }

    emit sgnl_MsgIDAboutToBeRemoved(msgIDToRemove);
    msgIDVector.removeOne(msgIDToRemove);
    emit sgnl_MsgIDRemoved(msgIDToRemove);
}

bool MsgIDFilterStore::containsMsgID(const MsgIDType &msgID) const
{
    return msgIDVector.contains(msgID);
}

const MsgIDType &MsgIDFilterStore::at(const int index) const
{
    return msgIDVector.at(index);
}

MsgIDType &MsgIDFilterStore::at(const int index)
{
    return msgIDVector[index];
}

int MsgIDFilterStore::size() const
{
    return msgIDVector.size();
}

int MsgIDFilterStore::indexOf(const MsgIDType &msgID) const
{
    return msgIDVector.indexOf(msgID);
}

void MsgIDFilterStore::clear()
{
    emit sgnl_AboutToBeCleared();
    msgIDVector.clear();
    emit sgnl_Cleared();
}
