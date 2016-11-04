#include "sysovrvtriggermodel.h"

SysOvrvTriggerModel::SysOvrvTriggerModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant SysOvrvTriggerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    switch(orientation)
    {
    case Qt::Horizontal:
        switch(section)
        {
        case 0:
            return QString("ID");
            break;
        case 1:
            return QString("Code");
            break;
        case 2:
            return QString("Trigger Type");
            break;
        }
    }
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
    // FIXME: Implement me!
}

QModelIndex SysOvrvTriggerModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int SysOvrvTriggerModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int SysOvrvTriggerModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return 3;
}

bool SysOvrvTriggerModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool SysOvrvTriggerModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void SysOvrvTriggerModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

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

    return Qt::ItemIsEditable; // FIXME: Implement me!
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
