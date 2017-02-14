#include "sendmsgmodel.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFont>
#include <QBrush>
#include <QTextEdit>

#include "idrep.h"
#include "msgtyperep.h"

#include <QDebug>

SendMsgModel::SendMsgModel(
                   QObject *parent
                   ) :
    QAbstractTableModel(parent)
{
}

SendMsgModel::~SendMsgModel()
{
    clear();
}

int SendMsgModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgPacketStorage.size();
}

int SendMsgModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COL_NR_OF_COLS;
}

QVariant SendMsgModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    const PrettyMsg &msgAtIndex = msgPacketStorage.at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        // returns only displayable data
        switch(col)
        {
            case COL_ID:
                return msgAtIndex.printIDName();
                break;
            case COL_CODE:
                return msgAtIndex.printCodeName();
                break;
            case COL_DATA:
                return msgAtIndex.printDataString();
                break;
        }
        break;
    case Qt::SizeHintRole:
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        //Background is drawn by delegate
        switch(col)
        {
            case COL_ID:
                return QBrush(msgAtIndex.getIDColor());
                break;
            case COL_CODE:
                return QBrush(msgAtIndex.getCodeColor());
                break;
            case COL_DATA:
                return QBrush(msgAtIndex.getDataColor());
                break;
        }
        break;
    case Qt::TextAlignmentRole:
        return Qt::TextWordWrap;
        break;
    case Qt::CheckStateRole:
        break;
    case DataUsr_RawData: //Qt::UserRole+0
        switch(col)
        {
            case COL_ID:
                return msgAtIndex.getId();
                break;
            case COL_CODE:
                return msgAtIndex.getCode();
                break;
            case COL_DATA:
                return QVariant::fromValue(msgAtIndex.getMsgData());
                break;
        }
        break;
    case Qt::UserRole +1:  // return Data
        //ToTHINK!!! DO NOT USE ADDRESSES OF DATASTORAGE...
        /* return QVariant::fromValue(static_cast<void*>(&(msgPacketStorage[row]))); */
        break;
    }

    return QVariant();
}

bool SendMsgModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();
    //ToDO if msgs should be editable
    if (role == Qt::EditRole)
    {
        //ToDO
        switch(col)
        {
            case COL_ID:
                break;
            case COL_CODE:
                break;
            case COL_DATA:
                break;
        }
    }
    return true;
}

QVariant SendMsgModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_ID:
                return QString("Name");
                break;
            case COL_CODE:
                return QString("Type");
                break;
            case COL_DATA:
                return QString("Data");
                break;
            }
        }
    }
    return QVariant();
}

bool SendMsgModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int msgModelSize = msgPacketStorage.size();
    if((row+count) < msgModelSize)
    {
        while(count--)
        {
            removeRow(row+count, parent);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void SendMsgModel::removeRow(int row, const QModelIndex &parent)
{
    int msgModelSize = msgPacketStorage.size();
    if(row < msgModelSize)
    {
        beginRemoveRows(parent, row, row);
        msgPacketStorage.remove(row);
        endRemoveRows();
    } else
    {
        qDebug() << "Index of row to remove not in model";
    }
}

void SendMsgModel::appendMsg(const PrettyMsg &msg)
{
    int newRow = msgPacketStorage.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    msgPacketStorage.append(msg);
    endInsertRows();
}

void SendMsgModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    msgPacketStorage.clear();
    endResetModel();
}

/* QByteArray SendMsgModel::ParseToJson() */
/* { */
/*     QJsonArray jsonMsgsArr; */
/*     int msgPacketStorageSize = msgPacketStorage.size(); */
/*     for(int i = 0; i < msgPacketStorageSize;++i) */
/*     { */
/*         const PrettyMsg &msg = msgPacketStorage.at(i); */
/*         jsonMsgsArr.append(msg.parseOUT()); */
/*     } */
/*     return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented); */
/* } */

/* void SendMsgModel::ParseFromJson(const QByteArray &jsonFile) */
/* { */
/*     this->clear(); */
/*     QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array(); */
/*     for(auto&& item : jsonMsgsArr) */
/*     { */
/*         PrettyMsg newMsg(item.toObject()); */
/*         appendMsg(newMsg); */
/*     } */
/* } */

QVector<PrettyMsg> SendMsgModel::getMsgPacket() const
{
    QVector<PrettyMsg> msgPacket;
    for(const PrettyMsg &msg : msgPacketStorage)
    {
        msgPacket.append(msg);
    }
    return msgPacket;
}

void SendMsgModel::setMsgPacket(const QVector<PrettyMsg> &msgPacket)
{
    clear();
    beginResetModel();
    for(const PrettyMsg &msg : msgPacket)
    {
        msgPacketStorage.append(msg);
    }
    endResetModel();
}

void SendMsgModel::slt_appendMsg(const PrettyMsg &newMsg)
{
    appendMsg(newMsg);
}

void SendMsgModel::slt_IDRepAdded(const IDRep &addedIDRep)
{
    setIDRepForID(addedIDRep.getId(),addedIDRep);
}
void SendMsgModel::slt_IDRepUpdated(const IDRep &updatedIDRep)
{
    setIDRepForID(updatedIDRep.getId(),updatedIDRep);
}
void SendMsgModel::slt_IDRepRemoved(const MsgIDType relatedID)
{
    setIDRepForID(relatedID, IDRep(relatedID));
}
void SendMsgModel::slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep)
{
    setMsgTypeRepForCode(addedMsgTypeRep.getCode(), addedMsgTypeRep);
}
void SendMsgModel::slt_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep)
{
    setMsgTypeRepForCode(updatedMsgTypeRep.getCode(), updatedMsgTypeRep);
}
void SendMsgModel::slt_MsgTypeRepRemoved(const MsgCodeType relatedCode)
{
    setMsgTypeRepForCode(relatedCode, MsgTypeRep(relatedCode));
}
/* void SendMsgModel::slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep); */
/* void SendMsgModel::slt_MsgDataRepUpdated(const MsgDataRep &changedMsgDataRep); */
/* void SendMsgModel::slt_MsgDataRepRemoved(const MsgCodeType codeWhoseDataRepWasRemoved); */

void SendMsgModel::setIDRepForID(const MsgIDType relatedID, const IDRep &idRepToSet)
{
    const int msgPacketStorageSize = msgPacketStorage.size();
    for(int i = 0; i < msgPacketStorageSize; ++i)
    {
        PrettyMsg &msg = msgPacketStorage.at(i);
        if(msg.getId() == relatedID)
        {
            msg.changeIDRep(idRepToSet);
            emit dataChanged(index(i,COL_ID), index(i,COL_ID), {Qt::DisplayRole, Qt::BackgroundRole, Qt::SizeHintRole});
        }
    }
}

void SendMsgModel::setMsgTypeRepForCode(const MsgCodeType relatedCode, const MsgTypeRep &msgTypeRepToSet)
{
    const int msgPacketStorageSize = msgPacketStorage.size();
    for(int i = 0; i < msgPacketStorageSize; ++i)
    {
        PrettyMsg &msg = msgPacketStorage.at(i);
        if(msg.getCode() == relatedCode)
        {
            msg.changeMsgTypeRep(msgTypeRepToSet);
            emit dataChanged(index(i,COL_CODE), index(i,COL_CODE), {Qt::DisplayRole, Qt::BackgroundRole, Qt::SizeHintRole});
        }
    }
}

