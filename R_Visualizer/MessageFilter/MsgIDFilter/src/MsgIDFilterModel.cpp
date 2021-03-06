#include "MsgIDFilterModel.h"

#include "IMsgIDFilterStore.h"

#include <QString>
#include <QColor>
#include <QBrush>
#include <QDebug>

MsgIDFilterModel::MsgIDFilterModel(
        IMsgIDFilterStore *msgIDFilterStore,
        QObject *parent) :
    QAbstractListModel(parent),
    msgIDFilterStore(msgIDFilterStore)
{
    connectToStore();
}

MsgIDFilterModel::~MsgIDFilterModel()
{
}

int MsgIDFilterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgIDFilterStore->size();
}

QVariant MsgIDFilterModel::data(
        const QModelIndex &index,
        int role
        ) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const int row = index.row();

    const MsgIDType &msgID = msgIDFilterStore->at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        return static_cast<QString>(msgID);
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        break;
    case Qt::TextAlignmentRole:
        break;
    case Qt::CheckStateRole:
        break;
    case Qt::UserRole:
        return QVariant::fromValue<MsgIDType>(msgID);
        break;
    }
    return QVariant();

}

QVariant MsgIDFilterModel::headerData(
        int section,
        Qt::Orientation orientation,
        int role
        ) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
                return QString("ID");
        }
    }
    return QVariant();
}

Qt::ItemFlags MsgIDFilterModel::flags(
        const QModelIndex &index
        ) const
{
    Q_UNUSED(index)

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool MsgIDFilterModel::setData(
        const QModelIndex &index,
        const QVariant &value,
        int role
        )
{
    const int row = index.row();
    bool altered = false;

    MsgIDType &msgID = msgIDFilterStore->at(row);

    switch(role)
    {
    case Qt::EditRole:
        msgID = MsgIDType(value.value<MsgIDType::type>());
        altered = true;
        break;
    }

    if(altered)
    {
        //ToDO EMIT SIGNALS!!! URGENT!!!
        emit dataChanged(index, index);
        emit sgnl_HasChanged();
        return true;
    }
    else
    {
        return false;
    }
}

bool MsgIDFilterModel::insertRows(
        int row,
        int count,
        const QModelIndex &parent
        )
{
    Q_UNUSED(parent)
}

bool MsgIDFilterModel::removeRows(
        int row,
        int count,
        const QModelIndex &parent
        )
{
    Q_UNUSED(parent)
    const int modelSize = msgIDFilterStore->size();
    if(!modelSize || ((row+count-1) >= modelSize))
    {
        return false;
    }

    //ToTHINK .. This is definitely for perfomance.. but it is clean

    /* beginRemoveRows(parent, row, row+count-1); */

    int cntr = count;

    while(cntr--)
    {
        msgIDFilterStore->removeMsgID(msgIDFilterStore->at(row+cntr));
    }
    /* msgIDStore.remove(row, count); */

    /* endRemoveRows(); */
    return true;
}

void MsgIDFilterModel::slt_MsgIDAboutToBeAdded(
        const MsgIDType &msgID
        )
{
    const int currentEndIndex = rowCount();
    emit beginInsertRows(QModelIndex(), currentEndIndex, currentEndIndex);
}

void MsgIDFilterModel::slt_MsgIDAdded(
        const MsgIDType &msgID
        )
{
    emit endInsertRows();
}

void MsgIDFilterModel::slt_MsgIDAboutToBeRemoved(
        const MsgIDType &msgID
        )
{
    const int index = msgIDFilterStore->indexOf(msgID);
    emit beginRemoveRows(QModelIndex(), index, index);
}

void MsgIDFilterModel::slt_MsgIDRemoved(
        const MsgIDType &msgID
        )
{
    emit endRemoveRows();
}

void MsgIDFilterModel::slt_AboutToBeCleared()
{
    emit beginResetModel();
}

void MsgIDFilterModel::slt_Cleared()
{
    emit endResetModel();
}

void MsgIDFilterModel::connectToStore()
{
    connect(
            msgIDFilterStore,
            &IMsgIDFilterStore::sgnl_MsgIDAboutToBeAdded,
            this,
            &MsgIDFilterModel::slt_MsgIDAboutToBeAdded
           );

    connect(
            msgIDFilterStore,
            &IMsgIDFilterStore::sgnl_MsgIDAdded,
            this,
            &MsgIDFilterModel::slt_MsgIDAdded
           );

    connect(
            msgIDFilterStore,
            &IMsgIDFilterStore::sgnl_MsgIDAboutToBeRemoved,
            this,
            &MsgIDFilterModel::slt_MsgIDAboutToBeRemoved
           );

    connect(
            msgIDFilterStore,
            &IMsgIDFilterStore::sgnl_MsgIDRemoved,
            this,
            &MsgIDFilterModel::slt_MsgIDRemoved
           );

    connect(
            msgIDFilterStore,
            &IMsgIDFilterStore::sgnl_AboutToBeCleared,
            this,
            &MsgIDFilterModel::slt_AboutToBeCleared
           );

    connect(
            msgIDFilterStore,
            &IMsgIDFilterStore::sgnl_Cleared,
            this,
            &MsgIDFilterModel::slt_Cleared
           );

    connect(
            this,
            &MsgIDFilterModel::sgnl_AddMsgIDToFilter,
            msgIDFilterStore,
            &IMsgIDFilterStore::slt_AddMsgIDToFilter
           );

    connect(
            this,
            &MsgIDFilterModel::sgnl_RemoveMsgIDFromFilter,
            msgIDFilterStore,
            &IMsgIDFilterStore::slt_RemoveMsgIDFromFilter
           );

    connect(
            this,
            &MsgIDFilterModel::sgnl_HasChanged,
            msgIDFilterStore,
            &IMsgIDFilterStore::sgnl_HasChanged
           );

}
