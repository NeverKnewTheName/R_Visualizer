#include "msgfilterproxymodel.h"

#include "msgmodel.h"

#include <QDateTime>
#include <QDebug>

MsgFilterProxyModel::MsgFilterProxyModel(FilterIDStore *filterIDModel, FilterCodeStore *filterCodeModel, QObject *parent) :
    QSortFilterProxyModel(parent),
    filterIDModel(filterIDModel),
    filterCodeModel(filterCodeModel),
    idFilterEnabled(false),
    codeFilterEnabled(false),
    timeStampFromFilterEnabled(false),
    timeStampToFilterEnabled(false)
{
}

bool MsgFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
//    qDebug() << __PRETTY_FUNCTION__;
    bool accepted = true;
    QModelIndex indexTimeStamp = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex indexID = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex indexMessage = sourceModel()->index(sourceRow, 2, sourceParent);

    if(idFilterEnabled)
        accepted = accepted && filterIDModel->containsID(indexID.data(Qt::UserRole+3).value<unsigned int>());
    if(codeFilterEnabled)
        accepted = accepted && filterCodeModel->containsCode(indexMessage.data(Qt::UserRole+3).value<unsigned int>());

//    qDebug() << accepted;
    return accepted;
}

bool MsgFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    int col = left.column();
    if( col == MsgModel::COL_TIMESTAMP ) return left.data(Qt::UserRole+3) < right.data(Qt::UserRole+3);
    if( col == MsgModel::COL_NAME ) return left.data(Qt::UserRole+3) < right.data(Qt::UserRole+3);
    if( col == MsgModel::COL_MESSAGE ) return left.data(Qt::UserRole + 3).value<MsgDataT>().code < right.data(Qt::UserRole + 3).value<MsgDataT>().code;

    return false;
}

void MsgFilterProxyModel::slt_RowsAdded(unsigned int nrOfRowsAdded)
{
    emit sgnl_RowsAdded(nrOfRowsAdded);
}

void MsgFilterProxyModel::slt_RowsRemoved(unsigned int nrOfRowsRemoved)
{
    emit sgnl_RowsDismissed(nrOfRowsRemoved);
}

void MsgFilterProxyModel::changeIDFilterEnabled(bool enabled)
{
//    beginResetModel();
    idFilterEnabled = enabled;
    invalidateFilter();
//    endResetModel();
}

void MsgFilterProxyModel::changeCodeFilterEnabled(bool enabled)
{
//    beginResetModel();
    codeFilterEnabled = enabled;
    invalidateFilter();
//    endResetModel();
}

void MsgFilterProxyModel::changeTimestampFromFilterEnabled(bool enabled)
{
    beginResetModel();
    timeStampFromFilterEnabled = enabled;
    invalidateFilter();
    endResetModel();
}

void MsgFilterProxyModel::changeTimestampToFilterEnabled(bool enabled)
{
    beginResetModel();
    timeStampToFilterEnabled = enabled;
    invalidateFilter();
    endResetModel();
}
