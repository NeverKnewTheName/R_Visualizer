#include "msgmodel.h"

#include "msg.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFont>
#include <QBrush>
#include <QTextEdit>

#include <QDebug>


MsgModel::MsgModel(const size_t nrOfMessagesToDisplay, QObject *parent) :
    QAbstractTableModel(parent),
    NrOfMessagesToDisplay(nrOfMessagesToDisplay),
    msgBuffer(nrOfMessagesToDisplay)
{
}

MsgModel::~MsgModel()
{
    this->clear();
}

int MsgModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgBuffer.size();
}

int MsgModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COL_NR_OF_COLS;
}

QVariant MsgModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    const Msg &msgAtIndex = msgBuffer.at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        // returns only displayable data
        if(col == COL_TIMESTAMP) return msgAtIndex.getTimestamp().toString("dd.MM.yyyy - hh:mm:ss.zzz");
        if(col == COL_NAME) return msgAtIndex.getId();
        if(col == COL_MESSAGE) return QString("Code: 0x%1\nData: %2").arg(msgAtIndex.getCode()).arg(msgAtIndex.getDataAsString());
//        if(col == COL_MESSAGE) return QTextEdit(QString("RABL\nRABL\nRABL\nRABL\n"));
        break;
    case Qt::SizeHintRole:
//        return QSize(100,40);
        return msgAtIndex.getMsgSizeHint();
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        //Background is drawn by delegate
        break;
    case Qt::TextAlignmentRole:
        return Qt::TextWordWrap;
        break;
    case Qt::CheckStateRole:
        break;
    case Qt::UserRole +1:  // return Data
        //ToTHINK!!! DO NOT USE ADDRESSES OF DATASTORAGE...
        return QVariant::fromValue(static_cast<void*>(&msgAtIndex));
        break;
    case Qt::UserRole +2:  // return Code of the line
        return msgAtIndex.getCode();
        break;
    case Qt::UserRole +3: // return raw data
        if(col == COL_TIMESTAMP) return msgAtIndex.getTimestamp();
        if(col == COL_NAME) return msgAtIndex.getId();
        if(col == COL_MESSAGE) return msgAtIndex.getCode();
        break;
    case Qt::UserRole +4:// return Keys for PixmapCache
        if(col == COL_TIMESTAMP)
        {
            return QString("PxmpCach_TmStmp%1").arg(msgAtIndex.getTimestamp().toString("dd.MM.yyyy - hh:mm:ss.zzz"));
        }
        if(col == COL_NAME)
        {
            return QString("PxmpCach_ID%1").arg(msgAtIndex.getId());
        }
        if(col == COL_MESSAGE)
        {
            QString MsgDataKey(QString("PxmpCach_MsgData_ID%1_Code%2_Data")
                    .arg(msgAtIndex.getCode())
                    .arg(msgAtIndex.getCode())
                               );
            for(auto & dataByte : msgAtIndex.getData()->DataBytes)
            {
                MsgDataKey.append(QString::number(dataByte));
            }
            return MsgDataKey;
        }
        break;
    }

    return QVariant();
}

bool MsgModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index)
    Q_UNUSED(value)
    //ToDO if msgs should be editable
    if (role == Qt::EditRole)
    {
        //msgs.at(index.row()) = value.toString();

        //emit editCompleted( result );
    }
    return true;
}

QVariant MsgModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_TIMESTAMP:
                return QString("Timestamp");
                break;
            case COL_NAME:
                return QString("Name");
                break;
            case COL_MESSAGE:
                return QString("Message");
                break;
            }
        }
    }
    return QVariant();
}

//This method is actually not suitable for a model for the MessageStream...
bool MsgModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int msgModelSize = msgBuff.size();
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

//This method is actually not suitable for a model for the MessageStream...
void MsgModel::removeRow(int row, const QModelIndex &parent)
{
    int msgModelSize = msgBuff.size();
    if(row < msgModelSize)
    {
        beginRemoveRows(parent, row, row);
        msgBuff.remove(row);
        endRemoveRows();
    } else
    {
        qDebug() << "Index of row to remove not in model";
    }
}

void MsgModel::addMsg(const Msg &msg)
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

void MsgModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    msgBuffer.clear();
    endResetModel();
}

//ToDELETE
RSimpleDestructiveRingBuff<Msg> MsgModel::getMsgs() const
{
    return msgBuff;
}

//ToDELETE
void MsgModel::setMsgs(const RSimpleDestructiveRingBuff<Msg> value)
{
    this->clear();
    beginInsertRows(QModelIndex(),0,value.size());
    int size = value.size();
    for( int i = 0; i < size; i++)
    {
        msgBuffer.append(value.at(i));
    }
    endInsertRows();
}

QByteArray MsgModel::parseToJSON()
{
    QJsonArray jsonMsgsArr;
    for(int i = 0; i < msgBuff.size();++i)
    {
        const Msg &msg = msgBuffer.at(i);
        jsonMsgsArr.append(msg.parseOUT());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void MsgModel::parseFromJSON(QByteArray jsonFile)
{
    this->clear();
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        const Msg &newMsg(item.toObject);
        addMsg(newMsg);
    }
}

void MsgModel::messageReceived(const Msg &msg)
{
    addMsg(msg);
}

