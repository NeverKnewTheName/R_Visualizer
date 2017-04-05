#ifndef MSGIDFILTERMODEL_H
#define MSGIDFILTERMODEL_H

#include <QAbstractListModel>

class MsgIDFilterModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MsgIDFilterModel(
            IMsgIDFilterStore *msgIDFilterStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgIDFilterModel();

    int rowCount(
            const QModelIndex &parent = QModelIndex()
            ) const Q_DECL_OVERRIDE;

    QVariant data(
            const QModelIndex &index,
            int role = Qt::DisplayRole
            ) const Q_DECL_OVERRIDE;

    QVariant headerData(
            int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole
            ) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(
            const QModelIndex &index
            ) const Q_DECL_OVERRIDE;

    bool insertRows(
            int row,
            int count,
            const QModelIndex &parent = QModelIndex()
            ) Q_DECL_OVERRIDE;

    bool removeRows(
            int row,
            int count,
            const QModelIndex &parent = QModelIndex()
            ) Q_DECL_OVERRIDE;


private:
    IMsgIDFilterStore *msgIDFilterStore;

};

#endif /* MSGIDFILTERMODEL_H */
