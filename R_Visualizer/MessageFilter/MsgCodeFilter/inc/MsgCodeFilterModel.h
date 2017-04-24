/**
 * @file MsgCodeFilterModel.h
 * @author Christian Neuberger
 * @date 2017-04-24
 * 
 * @brief Model for #MsgCodeType needed by the message code filter
 */
#ifndef MSGCODEFILTERMODEL_H
#define MSGCODEFILTERMODEL_H

#include <QAbstractListModel>

class IMsgCodeFilterStore;

/**
 * @brief The MsgCodeFilterModel
 */
class MsgCodeFilterModel :
    public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MsgCodeFilterModel(
            IMsgCodeFilterStore *msgCodeFilterStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeFilterModel();

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
    IMsgCodeFilterStore *msgCodeFilterStore;
};

#endif /* MSGCODEFILTERMODEL_H */
