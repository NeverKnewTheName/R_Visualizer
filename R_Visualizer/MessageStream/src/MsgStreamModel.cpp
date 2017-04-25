#include "MsgStreamModel.h"

#include <QBrush>
#include <QDebug>

#include "PrettyTimestampedMsg.h"

#include "IMsgStreamStore.h"

MsgStreamModel::MsgStreamModel(IMsgStreamStore *msgStreamStore,
        QObject *parent
        ) :
    QAbstractTableModel(parent),
    msgStreamStore(msgStreamStore)
{
    connectMsgStreamStore();
}

MsgStreamModel::~MsgStreamModel()
{
}


int MsgStreamModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgStreamStore->size();
}

int MsgStreamModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return MsgStreamModel::MsgStreamHeaderCol_NR_OF_COLS;
}

QVariant MsgStreamModel::data(
        const QModelIndex &index,
        int role
        ) const
{
    const int row = index.row();
    const int col = index.column();
    const IPrettyTimestampedMsg &msgAtIndex = msgStreamStore->at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        // returns only displayable data
        switch(col)
        {
            case MsgStreamModel::MsgStreamHeaderCol_Timestamp:
                return msgAtIndex.getTimestamp().
                    toString("dd.MM.yyyy - hh:mm:ss.zzz");
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Name:
                return msgAtIndex.getMsgIDPlainTextAlias();
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Type:
                return msgAtIndex.getMsgCodePlainTextAlias();
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Data:
                return msgAtIndex.getParsedMsgDataString();
                break;
            default:
                qDebug() << "ERROR: " << "Unknown COLUMN";
        }
        break;
    case Qt::SizeHintRole:
        //ToDO Calculate sizes...
        switch(col)
        {
            case MsgStreamModel::MsgStreamHeaderCol_Timestamp:
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Name:
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Type:
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Data:
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
            case MsgStreamModel::MsgStreamHeaderCol_Timestamp:
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Name:
                return QBrush(msgAtIndex.getMsgIDColorRepresentation());
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Type:
                return QBrush(msgAtIndex.getMsgCodeColorRepresentation());
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Data:
                return QBrush(msgAtIndex.getParsedMsgDataColor());
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
    case Qt::UserRole + 0: //DataUsr_RawData:  //Qt::UserRole +0: // return raw data
        switch(col)
        {
            case MsgStreamModel::MsgStreamHeaderCol_Timestamp:
                return msgAtIndex.getTimestamp();
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Name:
                return msgAtIndex.getMsgID();
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Type:
                return msgAtIndex.getMsgCode();
                break;
            case MsgStreamModel::MsgStreamHeaderCol_Data:
                return QVariant::fromValue(msgAtIndex.getMsgData());
                break;
            default:
                qDebug() << "ERROR: " << "Unknown COLUMN";
        }
        break;
    case Qt::UserRole + 1: //DataUsr_Msg:  //Qt::UserRole +1:  // return Data
        /* return msgAtIndex; */
        break;
    }

    return QVariant();

}

QVariant MsgStreamModel::headerData(
        int section,
        Qt::Orientation orientation,
        int role
        ) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
                case MsgStreamModel::MsgStreamHeaderCol_Timestamp:
                    return QString("Timestamp");
                    break;
                case MsgStreamModel::MsgStreamHeaderCol_Name:
                    return QString("Name");
                    break;
                case MsgStreamModel::MsgStreamHeaderCol_Type:
                    return QString("Type");
                    break;
                case MsgStreamModel::MsgStreamHeaderCol_Data:
                    return QString("Data");
                    break;
                default:
                    qDebug() << "ERROR: " << "Unknown COLUMN";
            }
        }
    }
    return QVariant();

}

void MsgStreamModel::slt_msgAboutToBeAppended()
{
    int newRowNumber = msgStreamStore->size();
    beginInsertRows(QModelIndex(),newRowNumber,newRowNumber);
}

void MsgStreamModel::slt_msgAppended()
{
    endInsertRows();
}

void MsgStreamModel::slt_msgAboutToBePrepended()
{
    beginInsertRows(QModelIndex(),0,0);
}

void MsgStreamModel::slt_msgPrepended()
{
    endInsertRows();
}

void MsgStreamModel::slt_storeAboutToOverflow()
{
    //ToTHINK how to do this better...
    //currently forcing all views to reload the entire model
    beginResetModel();
}

void MsgStreamModel::slt_storeOverflow()
{
    //ToTHINK how to do this better...
    //currently forcing all views to reload the entire model
    endResetModel();
}

void MsgStreamModel::slt_storeAboutToUnderflow()
{
    //ToTHINK how to do this better...
    //currently forcing all views to reload the entire model
    beginResetModel();
}

void MsgStreamModel::slt_storeUnderflow()
{
    //ToTHINK how to do this better...
    //currently forcing all views to reload the entire model
    endResetModel();
}

void MsgStreamModel::slt_storeAboutToBeCleared()
{
    beginResetModel();
}

void MsgStreamModel::slt_storeCleared()
{
    endResetModel();
}

void MsgStreamModel::connectMsgStreamStore()
{
    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_msgAboutToBeAppended,
            this,
            &MsgStreamModel::slt_msgAboutToBeAppended
           );

    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_msgAppended,
            this,
            &MsgStreamModel::slt_msgAppended
           );

    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_msgPrepended,
            this,
            &MsgStreamModel::slt_msgPrepended
           );

    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_msgAboutToBePrepended,
            this,
            &MsgStreamModel::slt_msgAboutToBePrepended
           );

    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_storeAboutToOverflow,
            this,
            &MsgStreamModel::slt_storeAboutToOverflow
           );

    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_storeOverflow,
            this,
            &MsgStreamModel::slt_storeOverflow
           );

    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_storeAboutToUnderflow,
            this,
            &MsgStreamModel::slt_storeAboutToUnderflow
           );

    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_storeUnderflow,
            this,
            &MsgStreamModel::slt_storeUnderflow
           );

    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_storeAboutToBeCleared,
            this,
            &MsgStreamModel::slt_storeAboutToBeCleared
           );

    connect(
            msgStreamStore,
            &IMsgStreamStore::sgnl_storeCleared,
            this,
            &MsgStreamModel::slt_storeCleared
           );
}
