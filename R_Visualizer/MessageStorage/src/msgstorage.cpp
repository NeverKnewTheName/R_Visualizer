#include "msgstorage.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "fileparser.h"

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

void MsgStorage::appendMsg(const Msg &newMsg)
{
    msgStore.append(newMsg);
    emit sgnl_MsgAdded(newMsg);
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

void MsgStorage::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

QString MsgStorage::saveMsgStorage(const QString &saveLocation)
{
    return msgStore.saveDataStorage(saveLocation);
}

void MsgStorage::slt_addMsg(const Msg &newMsg)
{
    appendMsg(newMsg);
}
