#include "errlogmodel.h"

ErrLogModel::ErrLogModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

int ErrLogModel::rowCount(const QModelIndex &parent) const
{
    return this->errLogStore.size();
}

int ErrLogModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COL_NR_OF_COLS;
}

QVariant ErrLogModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        // returns only displayable data
        if(col == COL_TIMESTAMP) return errLogStore.at(row)->getTimestamp().toString("dd.MM.yyyy - hh:mm:ss.zzz");
        if(col == COL_TX_ERR_CNTR) return errLogStore.at(row)->getTxErrCntr();
        if(col == COL_RX_ERR_CNTR) return errLogStore.at(row)->getRxErrCntr();
        if(col == COL_DETAILS) return errLogStore.at(row)->getDetailString();
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        break;
    case Qt::TextAlignmentRole:
        return Qt::TextWordWrap;
        break;
    case Qt::CheckStateRole:
        break;
    }

    return QVariant();
}

QVariant ErrLogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_TIMESTAMP:
                return QString("Timestamp");
                break;
            case COL_TX_ERR_CNTR:
                return QString("TX Error Counter");
                break;
            case COL_RX_ERR_CNTR:
                return QString("RX Error Counter");
                break;
            case COL_DETAILS:
                return QString("Details");
                break;
            }
        }
    }
    return QVariant();
}

bool ErrLogModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}


bool ErrLogModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return true;
}

void ErrLogModel::addErrEntry(ErrorLogEntry *errLogEntry)
{
    int newRow = this->errLogStore.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    this->errLogStore.append(errLogEntry);
    endInsertRows();
//    emit rowsAdded(1);
//    emit rowAppended(newRow);
}

void ErrLogModel::errLogMsgReceived(CAN_PacketPtr ptr)
{
    if( ptr->type() == CAN_Packet::Error_Frame )
    {
        Error_PacketPtr packet = qSharedPointerDynamicCast<Error_Packet>(ptr);
        QDateTime timeStamp = ptr->timestamp();
        int rxErrCntr = packet->RX_Error_Counter();
        int txErrCntr = packet->TX_Error_Counter();
        QString detailString = packet->Status_Register_String();

        this->addErrEntry(new ErrorLogEntry(timeStamp,rxErrCntr,txErrCntr,detailString));
    }
}
