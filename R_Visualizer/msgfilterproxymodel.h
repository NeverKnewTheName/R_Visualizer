#ifndef MSGFILTERPROXYMODEL_H
#define MSGFILTERPROXYMODEL_H

#include "MessageConfig/filteridstore.h"

#include <QSortFilterProxyModel>
#include <QHash>

class MsgProxyModel;

class MsgFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit MsgFilterProxyModel(FilterIDStore *filterIDModel, QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

private:
    FilterIDStore *filterIDModel;
    bool idFilterEnabled;
    friend class MsgProxyModel;
signals:

public slots:
    void changeIDFilterEnabled(bool enabled);
};

#endif // MSGFILTERPROXYMODEL_H
