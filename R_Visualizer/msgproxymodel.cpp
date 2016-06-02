#include "msgproxymodel.h"

#include "msgmodel.h"

#include <QDebug>


MsgProxyModel::MsgProxyModel(QObject *parent) : QAbstractProxyModel(parent), buffer(VISIBLEROWS)
{
    this->rowCntr = 0;
    this->visRowCntr = 0;
    //this->buffer = R_RingBuffer<QPersistentModelIndex>(VISIBLEROWS);
}

MsgProxyModel::~MsgProxyModel()
{

}

QModelIndex MsgProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
            return QModelIndex() ;
    return createIndex(row, column);
}

QModelIndex MsgProxyModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int MsgProxyModel::rowCount(const QModelIndex &parent) const
{
    return rowCntr;
}

int MsgProxyModel::columnCount(const QModelIndex &parent) const
{
    return sourceModel()->columnCount(parent);
}

QVariant MsgProxyModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    QModelIndex mappedIndex = mapToSource(index);
    if(!mappedIndex.isValid()) return QVariant();
    return sourceModel()->data(mappedIndex,role);
}

QVariant MsgProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return sourceModel()->headerData(section, orientation, role);
}

QModelIndex MsgProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if(sourceIndex.isValid())
    {
        QModelIndex proxyIndex = sourceModel()->index(sourceIndex.row()/*-visRowCntr*/, sourceIndex.column());
        return proxyIndex;
    }
    else
        return QModelIndex();
}

QModelIndex MsgProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    MsgModel* pModel = qobject_cast<MsgModel*>(sourceModel());
    if (/*!pModel ||*/ !proxyIndex.isValid()) return QModelIndex();
    QModelIndex mappedIndex = buffer.at(proxyIndex.row());
    //return pModel->createIndex(mappedIndex.row(), proxyIndex.column(), mappedIndex.internalId());
    int rowOffset = sourceModel()->rowCount();
    rowOffset = ( rowOffset > VISIBLEROWS ) ? rowOffset - VISIBLEROWS : 0;

    return pModel->createIndex((proxyIndex.row() + rowOffset), proxyIndex.column());
}

void MsgProxyModel::newEntryInSourceModel()
{
    qDebug() << "new Entries!" << rowCntr;

}

void MsgProxyModel::newEntryAppendedInSourceModel(QModelIndex &index)
{
    if(rowCntr < VISIBLEROWS)
    {
        ++rowCntr;
    }
    beginResetModel();

    buffer.push(QPersistentModelIndex(index));
    endResetModel();
}
