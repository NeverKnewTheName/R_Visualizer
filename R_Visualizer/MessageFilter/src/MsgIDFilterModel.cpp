#include "MsgIDFilterModel.h"

#include "IMsgIDFilterStore.h"

MsgIDFilterModel::MsgIDFilterModel(
        IMsgIDFilterStore *msgIDFilterStore,
        QObject *parent) :
    QAbstractListModel(parent),
    msgIDFilterStore(msgIDFilterStore)
{
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

}

QVariant MsgIDFilterModel::headerData(
        int section,
        Qt::Orientation orientation,
        int role
        ) const
{
}

Qt::ItemFlags MsgIDFilterModel::flags(
        const QModelIndex &index
        ) const
{
    Q_UNUSED(index)
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
}
