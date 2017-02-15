#include "msgstreammodel.h"

#include "msg.h"
#include "idrep.h"
#include "msgtyperep.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFont>
#include <QBrush>
#include <QTextEdit>

#include <QDebug>

#include "fileparser.h"


MsgStreamModel::MsgStreamModel(
        const size_t nrOfMessagesToDisplay,
        QObject *parent
        ) :
    QAbstractTableModel(parent),
    NrOfMessagesToDisplay(nrOfMessagesToDisplay),
    msgBuffer(nrOfMessagesToDisplay)
{
}

MsgStreamModel::~MsgStreamModel()
{
    this->clear();
}

int MsgStreamModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgBuffer.size();
}

int MsgStreamModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COL_NR_OF_COLS;
}

QVariant MsgStreamModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    const PrettyMsg &msgAtIndex = msgBuffer.at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        // returns only displayable data
        switch(col)
        {
            case COL_TIMESTAMP:
                return msgAtIndex.getTimestamp().toString("dd.MM.yyyy - hh:mm:ss.zzz");
                break;
            case COL_ID:
                return msgAtIndex.printIDName();
                break;
            case COL_CODE:
                return msgAtIndex.printCodeName();
                break;
            case COL_DATA:
                return msgAtIndex.printDataString();
                break;
            default:
                qDebug() << "ERROR: " << "Unknown COLUMN";
        }
        break;
    case Qt::SizeHintRole:
        //ToDO Calculate sizes...
        switch(col)
        {
            case COL_TIMESTAMP:
                break;
            case COL_ID:
                break;
            case COL_CODE:
                break;
            case COL_DATA:
                break;
            default:
                qDebug() << "ERROR: " << "Unknown COLUMN";
        }
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        switch(col)
        {
            case COL_TIMESTAMP:
                break;
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
        //Background is drawn by delegate
        break;
    case Qt::TextAlignmentRole:
        /* return (Qt::AlignLeft | Qt::AlignVCenter); */
        /* return Qt::TextWordWrap; */
        break;
    case Qt::CheckStateRole:
        break;
    case DataUsr_RawData:  //Qt::UserRole +0: // return raw data
        switch(col)
        {
            case COL_TIMESTAMP:
                return msgAtIndex.getTimestamp();
                break;
            case COL_ID:
                return msgAtIndex.getId();
                break;
            case COL_CODE:
                return msgAtIndex.getCode();
                break;
            case COL_DATA:
                return QVariant::fromValue(msgAtIndex.getMsgData());
                break;
            default:
                qDebug() << "ERROR: " << "Unknown COLUMN";
        }
        break;
    case DataUsr_Msg:  //Qt::UserRole +1:  // return Data
        /* return msgAtIndex; */
        break;
    }

    return QVariant();
}

QVariant MsgStreamModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_TIMESTAMP:
                //Timestamp of receival
                return QString("Timestamp");
                break;
            case COL_ID:
                //Name/ID of the Message
                return QString("Name");
                break;
            case COL_CODE:
                //Type/Code of the Message
                return QString("Type");
                break;
            case COL_DATA:
                //Message/Data of the Message
                return QString("Message");
                break;
            }
        }
        else
        {
            /* qDebug() << "Orientation not supported"; */
        }
    }
    return QVariant();
}

bool MsgStreamModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int msgBuffSize = msgBuffer.size();
    if((row+count) < msgBuffSize)
    {
        while(count--)
        {
            removeRow(row, parent);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void MsgStreamModel::removeRow(int row, const QModelIndex &parent)
{
    int msgBuffSize = msgBuffer.size();
    if(row < msgBuffSize)
    {
        beginRemoveRows(parent, row, row);
        msgBuffer.remove(row);
        endRemoveRows();
    }
    else
    {
        qDebug() << "Index of row to remove not in model!";
    }
}

void MsgStreamModel::appendMsg(const PrettyMsg &msg)
{
    /*
     * If the msg is to be displayed it has to be evaluated whether the msgBuffer is
     * already filled. 
     * If it is not filled, the msg is simply appended and 
     * the respective insertRows signals are emitted. 
     * If the buffer is already at its full capacity, the ringbuffer will adjust itself. 
     * Nonetheless the model has to be reset, to tell the view to invalidate its contents 
     * and redraw all messages.
     * Therefore, the msgBuffer needs to be kept as small as possible.. excessive reloading
     * of all messages will kill the PERFORMANCE!
     */

    int newRow = msgBuffer.size();
    if(newRow >= NrOfMessagesToDisplay)
    {
        //The buffer is filled, model needs to be invalidated/redrawn
        beginResetModel();
        msgBuffer.append(msg);
        endResetModel();
    }
    else
    {
        //The buffer is not yet filled, simply add Msg to buffer
        beginInsertRows(QModelIndex(),newRow,newRow);
        msgBuffer.append(msg);
        endInsertRows();
        emit rowAppended(newRow);
    }
}

void MsgStreamModel::prependMsg(const PrettyMsg &msg)
{
    if(msgBuffer.size() >= NrOfMessagesToDisplay)
    {
        beginResetModel();
        msgBuffer.prepend(msg);
        endResetModel();
    }
    else
    {
        beginInsertRows(QModelIndex(), 0,0);
        msgBuffer.prepend(msg);
        endInsertRows();
    }
}

void MsgStreamModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    msgBuffer.clear();
    endResetModel();
}

QByteArray MsgStreamModel::ParseToJson()
{
    QJsonArray jsonMsgsArr;
    int msgBuffSize = msgBuffer.size();
    for(int i = 0; i < msgBuffSize;++i)
    {
        const Msg &msg = msgBuffer.at(i);
        jsonMsgsArr.append(msg.ParseToJson());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void MsgStreamModel::ParseFromJson(const QByteArray &jsonFile)
{
    this->clear();
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        //ToDO
        /* const Msg newMsg(item.toObject); */
        /* appendMsg(newMsg); */
    }
}

void MsgStreamModel::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

void MsgStreamModel::messageReceived(const PrettyMsg &msg)
{
    appendMsg(msg);
}


void MsgStreamModel::slt_IDRepAdded(const IDRep &addedIDRep)
{
    setIDRepForID(addedIDRep.getId(), addedIDRep);
}

void MsgStreamModel::slt_IDRepUpdated(const IDRep &updatedIDRep)
{
    setIDRepForID(updatedIDRep.getId(), updatedIDRep);
}

void MsgStreamModel::slt_IDRepRemoved(const MsgIDType relatedID)
{
    setIDRepForID(relatedID, IDRep(relatedID));
}

void MsgStreamModel::slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep)
{
    setMsgTypeRepForCode(addedMsgTypeRep.getCode(), addedMsgTypeRep);
}

void MsgStreamModel::slt_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep)
{
    setMsgTypeRepForCode(updatedMsgTypeRep.getCode(), updatedMsgTypeRep);
}

void MsgStreamModel::slt_MsgTypeRepRemoved(const MsgCodeType relatedCode)
{
    setMsgTypeRepForCode(relatedCode, MsgTypeRep(relatedCode));
}

/* void MsgStreamModel::slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep) */
/* { */

/* } */

/* void MsgStreamModel::slt_MsgDataRepUpdated(const MsgDataRep &updatedMsgDataRep) */
/* { */

/* } */

/* void MsgStreamModel::slt_MsgDataRepRemoved(const MsgCodeType relatedCode) */
/* { */

/* } */

void MsgStreamModel::setIDRepForID(const MsgIDType relatedID, const IDRep &idRepToSet)
{
    const int msgBuffSize = msgBuffer.size();
    for(int i = 0; i < msgBuffSize; ++i)
    {
        PrettyMsg &msg = msgBuffer.at(i);
        if(msg.getId() == relatedID)
        {
            msg.changeIDRep(idRepToSet);
            emit dataChanged(index(i,COL_ID),index(i,COL_ID), {Qt::DisplayRole, Qt::BackgroundRole, Qt::SizeHintRole});
        }
    }
}

void MsgStreamModel::setMsgTypeRepForCode(const MsgCodeType relatedCode, const MsgTypeRep &msgTypeRepToSet)
{
    const int msgBuffSize = msgBuffer.size();
    for(int i = 0; i < msgBuffSize; ++i)
    {
        PrettyMsg &msg = msgBuffer.at(i);
        if(msg.getCode() == relatedCode)
        {
            //Since there is no special MsgTypeRep for the message anymore, use the plain one.
            msg.changeMsgTypeRep(msgTypeRepToSet);
            emit dataChanged(index(i,COL_CODE),index(i,COL_DATA), {Qt::DisplayRole, Qt::BackgroundRole, Qt::SizeHintRole});
            /* emit dataChanged(index(i,COL_CODE),index(i,COL_CODE), {Qt::DisplayRole, Qt::BackgroundRole, Qt::SizeHintRole}); */
            /* emit dataChanged(index(i,COL_DATA),index(i,COL_DATA), {Qt::DisplayRole, Qt::BackgroundRole, Qt::SizeHintRole}); */
        }
    }
}
