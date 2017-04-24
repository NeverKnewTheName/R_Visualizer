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
    const int col = index.column();

    const MsgCodeType &msgCode = msgCodeFilterStore->at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        return static_cast<QString>(msgCode);
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        return QBrush(QColor(Qt::white));
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
}

