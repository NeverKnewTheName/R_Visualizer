#include "msgproxymodel.h"

#include "msgmodel.h"

#include <QDebug>

#define VISIBLEROWS 10u

MsgProxyModel::MsgProxyModel(QObject *parent) : QAbstractProxyModel(parent)
{
    this->rowCntr = 0;
    this->visRowCntr = 0;
}

MsgProxyModel::~MsgProxyModel()
{

}

QModelIndex MsgProxyModel::index(int row, int column, const QModelIndex &parent) const
{
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

QModelIndex MsgProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if(sourceIndex.isValid())
    {
        //QModelIndex proxyIndex = QAbstractItemModel::createIndex(, sourceIndex.internalPointer());
        return sourceModel()->index(sourceIndex.row()/*-visRowCntr*/, sourceIndex.column());
    }
    else
        return QModelIndex();
}

QModelIndex MsgProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if(proxyIndex.isValid())
    {
        //QModelIndex sourceIndex = QAbstractItemModel::createIndex(proxyIndex.row()+visRowCntr, proxyIndex.column(), proxyIndex.internalPointer());
        return sourceModel()->index(proxyIndex.row()/*+visRowCntr*/, proxyIndex.column());
    }
    else
        return QModelIndex();
}

void MsgProxyModel::newEntryInSourceModel()
{
    qDebug() << "new Entries!" << rowCntr;
    if(rowCntr > VISIBLEROWS)
    {
        visRowCntr++;
    } else
    {
        rowCntr++;
    }
}
