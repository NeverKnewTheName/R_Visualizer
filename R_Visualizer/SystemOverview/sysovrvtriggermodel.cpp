#include "sysovrvtriggermodel.h"

SysOvrvTriggerModel::SysOvrvTriggerModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant SysOvrvTriggerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_ID:
                return QString("ID");
                break;
            case COL_Code:
                return QString("Code");
                break;
            case COL_TriggerType:
                return QString("Trigger Type");
                break;
            }
        }
    }
    return QVariant();
}

bool SysOvrvTriggerModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

QModelIndex SysOvrvTriggerModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return QModelIndex();
    }
    return this->createIndex(row,column);
}

QModelIndex SysOvrvTriggerModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
    QModelIndex();
}

int SysOvrvTriggerModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
    return 0;
}

int SysOvrvTriggerModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return COL_NR_OF_COLS;
}

//bool SysOvrvTriggerModel::hasChildren(const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//}

//bool SysOvrvTriggerModel::canFetchMore(const QModelIndex &parent) const
//{
//    // FIXME: Implement me!
//    return false;
//}

//void SysOvrvTriggerModel::fetchMore(const QModelIndex &parent)
//{
//    // FIXME: Implement me!
//}

QVariant SysOvrvTriggerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

bool SysOvrvTriggerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags SysOvrvTriggerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | QAbstractItemModel::flags(index);
}

bool SysOvrvTriggerModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool SysOvrvTriggerModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}
