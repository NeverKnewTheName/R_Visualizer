#include "SendMsgPackageModel.h"

#include "ISendMsgPackageStore.h"

#include "IMsg.h"

#include <QDebug>

SendMsgPackageModel::SendMsgPackageModel(
            ISendMsgPackageStore *sendMsgPackageStore,
            QObject *parent
            ) :
    QAbstractTableModel(parent),
    sendMsgPackageStore(sendMsgPackageStore)
{
    connectStore();

}

SendMsgPackageModel::~SendMsgPackageModel()
{
}

int SendMsgPackageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return sendMsgPackageStore->size();
}

int SendMsgPackageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return SendMsgPackageModel::COL_NR_OF_COLS;
}

QVariant SendMsgPackageModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const int col = index.column();
    const IMsg &msgAtIndex = sendMsgPackageStore->at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        // returns only displayable data
        switch(col)
        {
            case SendMsgPackageModel::COL_MsgID:
                return static_cast<QString>(msgAtIndex.getMsgID());
                break;
            case SendMsgPackageModel::COL_MsgCode:
                return static_cast<QString>(msgAtIndex.getMsgCode());
                break;
            case SendMsgPackageModel::COL_MsgData:
            {
                QString msgDataAsString;
                const MsgDataType &msgData = msgAtIndex.getMsgData();
                for(const MsgDataByteType &byte : msgData)
                {
                    msgDataAsString.prepend(static_cast<QString>(byte) + " ");
                }
                if(!msgDataAsString.isEmpty())
                {
                    msgDataAsString.prepend("0x ");
                }

                return msgDataAsString.simplified();
            }
                break;
            default:
                qDebug() << "ERROR: " << "Unknown COLUMN";
        }
        break;
    case Qt::SizeHintRole:
        //ToDO Calculate sizes...
        switch(col)
        {
            case SendMsgPackageModel::COL_MsgID:
                break;
            case SendMsgPackageModel::COL_MsgCode:
                break;
            case SendMsgPackageModel::COL_MsgData:
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
            case SendMsgPackageModel::COL_MsgID:
                break;
            case SendMsgPackageModel::COL_MsgCode:
                break;
            case SendMsgPackageModel::COL_MsgData:
                break;
        }
        break;
    case Qt::TextAlignmentRole:
        break;
    case Qt::CheckStateRole:
        break;
    case Qt::UserRole + 0: //DataUsr_RawData:  //Qt::UserRole +0: // return raw data
        switch(col)
        {
            case SendMsgPackageModel::COL_MsgID:
                return msgAtIndex.getMsgID();
                break;
            case SendMsgPackageModel::COL_MsgCode:
                return msgAtIndex.getMsgCode();
                break;
            case SendMsgPackageModel::COL_MsgData:
                return QVariant::fromValue(msgAtIndex.getMsgData());
                break;
            default:
                qDebug() << "ERROR: " << "Unknown COLUMN";
        }
        break;
    case Qt::UserRole +1:
        return QVariant::fromValue<const IMsg *>(&msgAtIndex);
    }
    return QVariant();
}

bool SendMsgPackageModel::setData(
        const QModelIndex &index,
        const QVariant &value,
        int role
        )
{
    const int row = index.row();
    const int col = index.column();
    IMsg &msgAtIndex = sendMsgPackageStore->at(row);

    bool edited = false;

    switch(role)
    {
    case Qt::EditRole:
        // returns only displayable data
        switch(col)
        {
            case SendMsgPackageModel::COL_MsgID:
                msgAtIndex.setMsgID(value.value<MsgIDType>());
                edited = true;
                break;
            case SendMsgPackageModel::COL_MsgCode:
                msgAtIndex.setMsgCode(value.value<MsgCodeType>());
                edited = true;
                break;
            case SendMsgPackageModel::COL_MsgData:
                msgAtIndex.setMsgData(value.value<MsgDataType>());
                edited = true;
                break;
            default:
                qDebug() << "ERROR: " << "Unknown COLUMN";
        }
        break;
    }

    if(edited)
    {
        emit dataChanged(index,index);
        emit sgnl_HasChanged();
    }

}

QVariant SendMsgPackageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
                case SendMsgPackageModel::COL_MsgID:
                    return QString("Name");
                    break;
                case SendMsgPackageModel::COL_MsgCode:
                    return QString("Type");
                    break;
                case SendMsgPackageModel::COL_MsgData:
                    return QString("Data");
                    break;
                default:
                    qDebug() << "ERROR: " << "Unknown COLUMN";
            }
        }
    }
    return QVariant();
}

bool SendMsgPackageModel::removeRows(int row, int count, const QModelIndex &parent)
{
    //ToDo
}

Qt::ItemFlags SendMsgPackageModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void SendMsgPackageModel::slt_msgAboutToBeInserted(const int index, const IMsg &msgToBePrepended)
{
    beginInsertRows(QModelIndex(),index,index);
}

void SendMsgPackageModel::slt_msgInserted(const int index, const IMsg &msgToBePrepended)
{
    endInsertRows();
}

void SendMsgPackageModel::slt_msgAboutToBeRemoved(
        const int index,
        const int count
        )
{
    beginRemoveRows(QModelIndex(),index,index+count);
}

void SendMsgPackageModel::slt_msgRemoved(
        const int index,
        const int count
        )
{
    endRemoveRows();
}

void SendMsgPackageModel::slt_AboutToBeCleared()
{
    beginResetModel();
}

void SendMsgPackageModel::slt_Cleared()
{
    endResetModel();
}

void SendMsgPackageModel::connectStore()
{
    connect(
            sendMsgPackageStore,
            &ISendMsgPackageStore::sgnl_msgAboutToBeInserted,
            this,
            &SendMsgPackageModel::slt_msgAboutToBeInserted
            );

    connect(
            sendMsgPackageStore,
            &ISendMsgPackageStore::sgnl_msgInserted,
            this,
            &SendMsgPackageModel::slt_msgInserted
            );

    connect(
            sendMsgPackageStore,
            &ISendMsgPackageStore::sgnl_msgAboutToBeRemoved,
            this,
            &SendMsgPackageModel::slt_msgAboutToBeRemoved
            );

    connect(
            sendMsgPackageStore,
            &ISendMsgPackageStore::sgnl_msgRemoved,
            this,
            &SendMsgPackageModel::slt_msgRemoved
            );

    connect(
            sendMsgPackageStore,
            &ISendMsgPackageStore::sgnl_AboutToBeCleared,
            this,
            &SendMsgPackageModel::slt_AboutToBeCleared
            );

    connect(
            sendMsgPackageStore,
            &ISendMsgPackageStore::sgnl_Cleared,
            this,
            &SendMsgPackageModel::slt_Cleared
            );

    connect(
            this,
            &SendMsgPackageModel::sgnl_HasChanged,
            sendMsgPackageStore,
            &ISendMsgPackageStore::sgnl_HasChanged
            );
}
