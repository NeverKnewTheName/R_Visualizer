#include "msgstreammodel.h"

#include "msg.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFont>
#include <QBrush>
#include <QTextEdit>

#include <QDebug>


MsgStreamModel::MsgStreamModel(
        const size_t nrOfMessagesToDisplay,
        const FilterIDStore &filterIDModel,
        const FilterCodeStore &filterCodeModel,
        const FilterTimestampStore &filterTimestampModel,
        QObject *parent
        ) :
    QAbstractTableModel(parent),
    NrOfMessagesToDisplay(nrOfMessagesToDisplay),
    msgBuffer(nrOfMessagesToDisplay),
    FilterIDModel(filterIDModel),
    FilterCodeModel(filterCodeModel),
    FilterTimestampModel(filterTimestampModel)
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
    const Msg &msgAtIndex = msgBuffer.at(row);

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
                return msgAtIndex.getId();
                break;
            case COL_CODE:
                return msgAtIndex.getCode();
                break;
            case COL_DATA:
                return QString("Code: 0x%1\nData: %2")
                        .arg(msgAtIndex.getCode())
                        .arg(msgAtIndex.getDataAsString());
                break;
            default:
                qDebug() << "ERROR: " << "Unknown COLUMN";
        }
        break;
    case Qt::SizeHintRole:
//        return QSize(100,40);
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
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
            qDebug() << "Orientation not supported";
        }
    }
    return QVariant();
}

void MsgStreamModel::addMsg(const Msg &msg)
{
    /*
     * addMsg must validate if the incoming msg shall be displayed (filters)
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

    //ToDO Apply filters!
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
        emit rowInvalidated(createIndex(newRow,2));
        emit rowInvalidated(createIndex(newRow,1));
        emit rowsAdded(1);
        emit rowAppended(newRow);
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
        /* addMsg(newMsg); */
    }
}

void MsgStreamModel::messageReceived(const Msg &msg)
{
    addMsg(msg);
}

void MsgStreamModel::slt_IDRepAdded(const IDRep &addedIDRep)
{

}

void MsgStreamModel::slt_IDRepUpdated(const IDRep &changedIDRep)
{

}

void MsgStreamModel::slt_IDRepRemoved(const MsgIDType idWhoseIDRepWasRemoved)
{

}

void MsgStreamModel::slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep)
{

}

void MsgStreamModel::slt_MsgTypeRepUpdated(const MsgTypeRep &changedMsgTypeRep)
{

}

void MsgStreamModel::slt_MsgTypeRepRemoved(const MsgCodeType codeWhoseMsgTypeRepWasRemoved)
{

}

/* void MsgStreamModel::slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep) */
/* { */

/* } */

/* void MsgStreamModel::slt_MsgDataRepUpdated(const MsgDataRep &changedMsgDataRep) */
/* { */

/* } */

/* void MsgStreamModel::slt_MsgDataRepRemoved(const MsgCodeType codeWhoseDataRepWasRemoved) */
/* { */

/* } */
