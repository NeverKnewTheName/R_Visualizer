#include "filtercodestore.h"

#include <QBrush>
#include <QDebug>

#include "fileparser.h"

FilterCodeStore::FilterCodeStore(QObject *parent) : QAbstractListModel(parent)
{

}


int FilterCodeStore::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return codeStore.size();
}

QVariant FilterCodeStore::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    switch(role)
    {
    case Qt::DisplayRole:
    {
        return codeStore.at(row);
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
    }
    return QVariant();
}

QVariant FilterCodeStore::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
                return QString("Code/Name");
        }
    }
    return QVariant();
}

bool FilterCodeStore::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    switch(role)
    {
    case Qt::EditRole:
        codeStore[row] = value.value<unsigned int>();
        emit internalModelChanged();
        return true;
        break;
    }
    return false;
}

Qt::ItemFlags FilterCodeStore::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool FilterCodeStore::removeRows(int row, int count, const QModelIndex &parent)
{
    int modelSize = codeStore.size();
    if(modelSize || ((row+count) < modelSize))
    {
        while(count--)
            removeRow(row+count, parent);
        return true;
    }
    else
    {
        return false;
    }
}

void FilterCodeStore::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    codeStore.remove(row);
    endRemoveRows();
}

void FilterCodeStore::addCode(const MsgCodeType code)
{
    beginInsertRows(QModelIndex(), codeStore.size(), codeStore.size());
    codeStore.append(code);
    endInsertRows();
    tempIndex = this->index(codeStore.size()-1);
    qDebug() << "Code:" << tempIndex.row();
    emit rowAdded(tempIndex);
}

void FilterCodeStore::addCode(const QString &codeString)
{
    beginInsertRows(QModelIndex(), codeStore.size(), codeStore.size());
    codeStore.append(codeString.toUInt());
    endInsertRows();
    tempIndex = this->index(codeStore.size()-1);
    qDebug() << "Code:" << tempIndex.row();
    emit rowAdded(tempIndex);
}

void FilterCodeStore::removeCode(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(),index.row(), index.row());
    codeStore.remove(index.row());
    endRemoveRows();
    emit internalModelChanged();
}

bool FilterCodeStore::containsCode(const MsgCodeType code) const
{
    return codeStore.contains(code);
}

const int FilterCodeStore::size() const
{
    return codeStore.size();
}

const MsgCodeType FilterCodeStore::at(const int index) const
{
    return codeStore.at(index);
}

void FilterCodeStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
