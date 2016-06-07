#ifndef MSGFILTERPROXYMODEL_H
#define MSGFILTERPROXYMODEL_H

#include "MessageConfig/filteridstore.h"
#include "MessageConfig/filtercodestore.h"


#include <QSortFilterProxyModel>
#include <QHash>


class MsgFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit MsgFilterProxyModel(FilterIDStore *filterIDModel, FilterCodeStore *filterCodeModel, QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

protected:
    FilterIDStore *filterIDModel;
    FilterCodeStore *filterCodeModel;
    bool idFilterEnabled;
    bool codeFilterEnabled;
    bool timeStampFromFilterEnabled;
    bool timeStampToFilterEnabled;

signals:
    void sgnl_RowsAdded(unsigned int nrOfRowsAdded);
    void sgnl_RowsDismissed(unsigned int nrOfRowsDismissed);

public slots:
    void slt_RowsAdded(unsigned int nrOfRowsAdded);
    void slt_RowsRemoved(unsigned int nrOfRowsRemoved);

    void changeIDFilterEnabled(bool enabled);
    void changeCodeFilterEnabled(bool enabled);
    void changeTimestampFromFilterEnabled(bool enabled);
    void changeTimestampToFilterEnabled(bool enabled);
};

#endif // MSGFILTERPROXYMODEL_H
