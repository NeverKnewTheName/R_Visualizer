#include "MsgIDFilterStore.h"

#include <QString>
#include <QDebug>

MsgIDFilterStore::MsgIDFilterStore()
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

    msgIDVector.append(msgIDToAdd);
}

void MsgIDFilterStore::removeMsgID(const MsgIDType &msgIDToRemove)
{
    if(!msgIDVector.contains(msgIDToRemove))
    {
        qDebug() << "MsgIDStore does not contain: "
            << static_cast<QString>(msgIDToRemove);
        return;
    }

    msgIDVector.removeOne(msgIDToRemove);
}

bool MsgIDFilterStore::containsMsgID(const MsgIDType &msgID) const
{
    return msgIDVector.contains(msgID);
}

MsgIDType MsgIDFilterStore::at(int index) const
{
    return msgIDVector.at(index);
}

int MsgIDFilterStore::size() const
{
    return msgIDVector.size();
}

void MsgIDFilterStore::clear()
{
    msgIDVector.clear();
}
