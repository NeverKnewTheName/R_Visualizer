#include "msgproxymodel.h"

#include "msgmodel.h"

#include <QDebug>


MsgProxyModel::MsgProxyModel(QObject *parent) :
    QAbstractProxyModel(parent),
    scrollOffset(0),
    rowOffset(0),
    rowCntr(0),
    visibleRows(VISIBLEROWS),
    continuous(true)
{

}

MsgProxyModel::MsgProxyModel(unsigned int visibleRows, QObject *parent) :
    QAbstractProxyModel(parent),
    scrollOffset(0),
    rowOffset(0),
    rowCntr(0),
    visibleRows(visibleRows),
    continuous(true)
{
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
    if(!sourceIndex.isValid()) return QModelIndex();

    return createIndex(sourceIndex.row() - rowOffset, sourceIndex.column());
}

QModelIndex MsgProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    MsgModel* pModel = qobject_cast<MsgModel*>(sourceModel());
    if (!pModel || !proxyIndex.isValid()) return QModelIndex();

    return pModel->createIndex((proxyIndex.row() + rowOffset), proxyIndex.column());
}

void MsgProxyModel::newEntryInSourceModel()
{
    qDebug() << "new Entries!" << rowCntr;
}

void MsgProxyModel::newEntryAppendedInSourceModel(QModelIndex &index)
{
    beginResetModel();
    if(rowCntr < visibleRows) rowCntr++;

    qDebug() << "ROW INSERT";
    if( continuous )
    {
        rowOffset = sourceModel()->rowCount();
        rowOffset = ( rowOffset > visibleRows ) ? rowOffset - visibleRows : 0;
        emit rowAppended();
    }
    qDebug() << rowOffset;
    endResetModel();
}

void MsgProxyModel::continuousChange(bool state)
{
    qDebug() << "Continuous state changed: " << state;
    continuous = state;
}

void MsgProxyModel::fetchRowsFromSource(int direction)
{
    qDebug() << "fetchRows in direction" << direction;
    if((direction < 0) && rowOffset)
    {
        beginResetModel();
        rowOffset--;
        endResetModel();
        emit rowFetched(+2);
    }
    else if((direction > 0) && ((rowOffset + visibleRows) < sourceModel()->rowCount()) )
    {
        beginResetModel();
        rowOffset++;
        endResetModel();
        emit rowFetched(-2);
    }
}
