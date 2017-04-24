#include "MsgCodeFilterModel.h"

#include "IMsgCodeFilterStore.h"

#include <QString>
#include <QColor>
#include <QBrush>
#include <QDebug>

MsgCodeFilterModel::MsgCodeFilterModel(
        IMsgCodeFilterStore *msgCodeFilterStore,
        QObject *parent) :
    QAbstractListModel(parent),
    msgCodeFilterStore(msgCodeFilterStore)
{
    connectToStore();
}

MsgCodeFilterModel::~MsgCodeFilterModel()
{
}

int MsgCodeFilterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgCodeFilterStore->size();
}

QVariant MsgCodeFilterModel::data(
        const QModelIndex &index,
        int role
        ) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const int row = index.row();

    const MsgCodeType &msgCode = msgCodeFilterStore->at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        return static_cast<QString>(msgCode);
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        break;
    case Qt::TextAlignmentRole:
        break;
    case Qt::CheckStateRole:
        break;
    }
    return QVariant();

}

QVariant MsgCodeFilterModel::headerData(
        int section,
        Qt::Orientation orientation,
        int role
        ) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
                return QString("Code");
        }
    }
    return QVariant();
}

Qt::ItemFlags MsgCodeFilterModel::flags(
        const QModelIndex &index
        ) const
{
    Q_UNUSED(index)

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool MsgCodeFilterModel::setData(
        const QModelIndex &index,
        const QVariant &value,
        int role
        )
{
    const int row = index.row();
    bool altered = false;

    MsgCodeType &msgCode = msgCodeFilterStore->at(row);

    switch(role)
    {
    case Qt::EditRole:
        msgCode = MsgCodeType(value.value<MsgCodeType::type>());
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

bool MsgCodeFilterModel::insertRows(
        int row,
        int count,
        const QModelIndex &parent
        )
{
    Q_UNUSED(parent)
}

bool MsgCodeFilterModel::removeRows(
        int row,
        int count,
        const QModelIndex &parent
        )
{
    Q_UNUSED(parent)
    const int modelSize = msgCodeFilterStore->size();
    if(!modelSize || ((row+count-1) >= modelSize))
    {
        return false;
    }

    //ToTHINK .. This is definitely for perfomance.. but it is clean

    /* beginRemoveRows(parent, row, row+count-1); */

    int cntr = count;

    while(cntr--)
    {
        msgCodeFilterStore->removeMsgCode(msgCodeFilterStore->at(row+cntr));
    }
    /* msgCodeStore.remove(row, count); */

    /* endRemoveRows(); */
    return true;
}

void MsgCodeFilterModel::slt_MsgCodeAboutToBeAdded(
        const MsgCodeType &msgCode
        )
{
    const int currentEndIndex = rowCount();
    emit beginInsertRows(QModelIndex(), currentEndIndex, currentEndIndex);
}

void MsgCodeFilterModel::slt_MsgCodeAdded(
        const MsgCodeType &msgCode
        )
{
    emit endInsertRows();
}

void MsgCodeFilterModel::slt_MsgCodeAboutToBeRemoved(
        const MsgCodeType &msgCode
        )
{
    const int index = msgCodeFilterStore->indexOf(msgCode);
    emit beginRemoveRows(QModelIndex(), index, index);
}

void MsgCodeFilterModel::slt_MsgCodeRemoved(
        const MsgCodeType &msgCode
        )
{
    emit endRemoveRows();
}

void MsgCodeFilterModel::slt_AboutToBeCleared()
{
    emit beginResetModel();
}

void MsgCodeFilterModel::slt_Cleared()
{
    emit endResetModel();
}

void MsgCodeFilterModel::connectToStore()
{
    connect(
            msgCodeFilterStore,
            &IMsgCodeFilterStore::sgnl_MsgCodeAboutToBeAdded,
            this,
            &MsgCodeFilterModel::slt_MsgCodeAboutToBeAdded
           );

    connect(
            msgCodeFilterStore,
            &IMsgCodeFilterStore::sgnl_MsgCodeAdded,
            this,
            &MsgCodeFilterModel::slt_MsgCodeAdded
           );

    connect(
            msgCodeFilterStore,
            &IMsgCodeFilterStore::sgnl_MsgCodeAboutToBeRemoved,
            this,
            &MsgCodeFilterModel::slt_MsgCodeAboutToBeRemoved
           );

    connect(
            msgCodeFilterStore,
            &IMsgCodeFilterStore::sgnl_MsgCodeRemoved,
            this,
            &MsgCodeFilterModel::slt_MsgCodeRemoved
           );

    connect(
            msgCodeFilterStore,
            &IMsgCodeFilterStore::sgnl_AboutToBeCleared,
            this,
            &MsgCodeFilterModel::slt_AboutToBeCleared
           );

    connect(
            msgCodeFilterStore,
            &IMsgCodeFilterStore::sgnl_Cleared,
            this,
            &MsgCodeFilterModel::slt_Cleared
           );

    connect(
            this,
            &MsgCodeFilterModel::sgnl_AddMsgCodeToFilter,
            msgCodeFilterStore,
            &IMsgCodeFilterStore::slt_AddMsgCodeToFilter
           );

    connect(
            this,
            &MsgCodeFilterModel::sgnl_RemoveMsgCodeFromFilter,
            msgCodeFilterStore,
            &IMsgCodeFilterStore::slt_RemoveMsgCodeFromFilter
           );

    connect(
            this,
            &MsgCodeFilterModel::sgnl_HasChanged,
            msgCodeFilterStore,
            &IMsgCodeFilterStore::sgnl_HasChanged
           );

}
