#include "msgproxymodel.h"

#include "msgmodel.h"
#include "msgfilterproxymodel.h"

#include <QDebug>


MsgProxyModel::MsgProxyModel(QObject *parent) :
    QAbstractProxyModel(parent),
    continuous(true),
    rowCntr(0),
    visibleRows(VISIBLEROWS),
    rowOffset(0),
    scrollOffset(0)
{

}

MsgProxyModel::MsgProxyModel(unsigned int visibleRows, QObject *parent) :
    QAbstractProxyModel(parent),
    continuous(true),
    rowCntr(0),
    visibleRows(visibleRows),
    rowOffset(0),
    scrollOffset(0)
{
}

MsgProxyModel::~MsgProxyModel()
{

}

QModelIndex MsgProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    return createIndex(row, column);
}

QModelIndex MsgProxyModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int MsgProxyModel::rowCount(const QModelIndex &parent) const
{
    if(!sourceModel()) return 0;
//    qDebug() << __PRETTY_FUNCTION__ << rowCntr;
    return rowCntr;
}

int MsgProxyModel::columnCount(const QModelIndex &parent) const
{
    if(!sourceModel()) return 0;
    return sourceModel()->columnCount(mapToSource(parent));
}

QVariant MsgProxyModel::data(const QModelIndex &index, int role) const
{
//    qDebug() << __PRETTY_FUNCTION__;
    if(!sourceModel()) return QVariant();
    if(!index.isValid()) return QVariant();
//    qDebug() << "Valid source";
    return sourceModel()->data(mapToSource(index),role);
}

QVariant MsgProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(!sourceModel()) return QVariant();
    return sourceModel()->headerData(section, orientation, role);
}

QModelIndex MsgProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
//    qDebug() << __PRETTY_FUNCTION__;
    if(!sourceIndex.isValid()) return QModelIndex();
//    qDebug() << "Valid index";
    return index(sourceIndex.row() - rowOffset, sourceIndex.column(),sourceIndex.parent());
}

QModelIndex MsgProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
//    qDebug() << __PRETTY_FUNCTION__;
    //    MsgModel* pModel = qobject_cast<MsgModel*>(sourceModel());
    //    if (!pModel || !proxyIndex.isValid()) return QModelIndex();

    //    return pModel->createIndex((proxyIndex.row() + rowOffset), proxyIndex.column());//
//    MsgFilterProxyModel* pModel = qobject_cast<MsgFilterProxyModel*>(sourceModel());
//    if (!pModel || !proxyIndex.isValid()) return QModelIndex();
    if(!sourceModel()) return QModelIndex();
//    qDebug() << "Valid index";
    return sourceModel()->index(proxyIndex.row() + rowOffset, proxyIndex.column(), proxyIndex.parent());
    //return pModel->index((proxyIndex.row() + rowOffset), proxyIndex.column());
//    return sourceModel->createIndex((proxyIndex.row() + rowOffset), proxyIndex.column());
}

void MsgProxyModel::newEntryInSourceModel()
{
    qDebug() << "new Entries!" << rowCntr;
}

void MsgProxyModel::newEntryAppendedInSourceModel(QModelIndex &index)
{
    beginResetModel();
    if(rowCntr < visibleRows) rowCntr++;

//    qDebug() << "ROW INSERT";
    if( continuous )
    {
        rowOffset = sourceModel()->rowCount();
        rowOffset = ( rowOffset > visibleRows ) ? rowOffset - visibleRows : 0;
        emit rowAppended();
    }
//    qDebug() << rowOffset;
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
