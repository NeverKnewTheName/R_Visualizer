#include "msgfilterproxymodel.h"

#include "msgmodel.h"

#include <QDateTime>

MsgFilterProxyModel::MsgFilterProxyModel(FilterIDStore *filterIDModel, QObject *parent) :
    QSortFilterProxyModel(parent),
    filterIDModel(filterIDModel),
    idFilterEnabled(false)
{
}

bool MsgFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex indexTimeStamp = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex indexID = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex indexMessage = sourceModel()->index(sourceRow, 2, sourceParent);

    if(idFilterEnabled)
        return filterIDModel->containsID(indexID.data(Qt::UserRole+3).value<unsigned int>());

    return true;
}

bool MsgFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    int col = left.column();
    if( col == MsgModel::COL_TIMESTAMP ) return left.data(Qt::UserRole+3) < right.data(Qt::UserRole+3);
    if( col == MsgModel::COL_NAME ) return left.data(Qt::UserRole+3) < right.data(Qt::UserRole+3);
    if( col == MsgModel::COL_MESSAGE ) return left.data(Qt::UserRole + 3).value<MsgDataT>().code < right.data(Qt::UserRole + 3).value<MsgDataT>().code;

    return false;
}

void MsgFilterProxyModel::changeIDFilterEnabled(bool enabled)
{
    beginResetModel();
    idFilterEnabled = enabled;
    invalidateFilter();
    endResetModel();
}
