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
    if(msgIDVector.contains(msgIDtoAdd))
    {
        qDebug() << "MsgIDStore does already contain: "
            << static_cast<QString>(msgIDToAdd);
        return;
    }

    msgIDVector.append(msgIDToAdd);
}

void MsgIDFilterStore::removeMsgID(const MsgIDType &msgIDToRemove)
{
    if(!msgIDVector.contains(msgIDtoAdd))
    {
        qDebug() << "MsgIDStore does not contain: "
            << static_cast<QString>(msgIDToAdd);
        return;
    }

    msgIDVector.removeOne(msgIDToRemove);
}

MsgIDFilterStore::containsMsgID(const MsgIDType &msgID) const
{
    return msgIDVector.contains(msgID);
}

MsgIDFilterStore::clear()
{
    msgIDVector.clear();
}
