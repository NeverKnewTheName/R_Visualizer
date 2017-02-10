#include "filteridstore.h"

#include <QBrush>
#include <QDebug>

FilterIDStore::FilterIDStore(QObject *parent) : QAbstractListModel(parent)
{

}

int FilterIDStore::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return idStore.size();
}

QVariant FilterIDStore::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    switch(role)
    {
    case Qt::DisplayRole:
    {
        return idStore.at(row);
    }
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        break;
    case Qt::TextAlignmentRole:
        break;
    case Qt::CheckStateRole:
        break;
    case Qt::UserRole: //UserRole is used for returning raw data for the IDDelegate
            return idStore.at(row);
            break;
    }
    return QVariant();
}

QVariant FilterIDStore::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    switch(role)
    {
        case Qt::DisplayRole:
            if (orientation == Qt::Horizontal)
            {
                return QString("ID/Name");
            }
    }
    return QVariant();
}

bool FilterIDStore::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    switch(role)
    {
    case Qt::EditRole:
        idStore[row] = value.value<int>();
        emit internalModelChanged();
        return true;
        break;
    }
    return false;
}

Qt::ItemFlags FilterIDStore::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool FilterIDStore::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    int modelSize = idStore.size();
    if(modelSize || ((row+count) < modelSize))
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

void FilterIDStore::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    beginRemoveRows(parent, row, row);
    idStore.remove(row);
    endRemoveRows();
}

QModelIndex FilterIDStore::addID(const MsgIDType id)
{
    beginInsertRows(QModelIndex(), idStore.size(), idStore.size());
    idStore.append(id);
    endInsertRows();
    QModelIndex tempIndex = index(idStore.size()-1);
    qDebug() << "Index:" << tempIndex.row();
    emit rowAdded(tempIndex);
    return tempIndex;
}

void FilterIDStore::removeID(QModelIndex &index)
{
    beginRemoveRows(QModelIndex(),index.row(), index.row());
    idStore.remove(index.row());
    endRemoveRows();
    emit internalModelChanged();
    //Better: emit row removed...
}

void FilterIDStore::removeID(const MsgIDType id)
{
    int row = idStore.indexOf(id);
    QModelIndex tempIndex = index(row);
    if(!tempIndex.isValid())
    {
        return;
    }
    removeID(tempIndex);
}

bool FilterIDStore::containsID(const MsgIDType id) const
{
    return idStore.contains(id);
}
