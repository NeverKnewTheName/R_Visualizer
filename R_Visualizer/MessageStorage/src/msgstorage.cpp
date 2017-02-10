#include "msgstorage.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

MsgStorage::MsgStorage(QObject *parent) :
    QObject(parent),
    msgStore(1000, 3)
{
}

Msg MsgStorage::at(const size_t index)
{
    return msgStore.at(index);
}

Msg MsgStorage::operator[](const size_t index)
{
    return msgStore[index];
}

void MsgStorage::clear()
{
    msgStore.clear();
    emit sgnl_StoreCleared();
}

int MsgStorage::size() const
{
    return msgStore.size();
}

bool MsgStorage::isEmpty() const
{
    return msgStore.isEmpty();
}


QJsonDocument MsgStorage::ParseToJson() const
{
    /* return msgStore.ParseToJson(); */
    qDebug() << "Parse to json currently not available in MsgStorage";
    return QJsonDocument();
}

bool MsgStorage::ParseFromJson(const QJsonArray &jsonMsgsArray)
{
    /* return msgStore.ParseFromJson(jsonMsgsArray); */
    qDebug() << "Parse from json currently not available in MsgStorage";
    return false;
}

void MsgStorage::slt_addMsg(const Msg &newMsg)
{
    msgStore.append(newMsg);
}
