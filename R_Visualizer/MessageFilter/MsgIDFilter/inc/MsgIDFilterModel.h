/**
 * @file MsgIDFilterModel.h
 * @author Christian Neuberger
 * @date 2017-04-24
 * 
 * @brief Model for #MsgIDType needed by the message id filter
 */
#ifndef MSGIDFILTERMODEL_H
#define MSGIDFILTERMODEL_H

#include <QAbstractListModel>

#include "MsgIDType.h"

class IMsgIDFilterStore;

/**
 * @addtogroup MsgIDFilterGroup
 * 
 * @{
 */

/**
 * @brief The MsgIDFilterModel
 */
class MsgIDFilterModel :
    public QAbstractListModel
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

    bool setData(
            const QModelIndex &index,
            const QVariant &value,
            int role
            ) Q_DECL_OVERRIDE;

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

signals:

    void sgnl_AddMsgIDToFilter(
            const MsgIDType &msgIDToAdd
        );

    void sgnl_RemoveMsgIDFromFilter(
            const MsgIDType &msgIDToRemove
        );

    void sgnl_HasChanged();

public slots:
    void slt_MsgIDAboutToBeAdded(
            const MsgIDType &msgID
            );

    void slt_MsgIDAdded(
            const MsgIDType &msgID
            );

    void slt_MsgIDAboutToBeRemoved(
            const MsgIDType &msgID
            );

    void slt_MsgIDRemoved(
            const MsgIDType &msgID
            );

    void slt_AboutToBeCleared();

    void slt_Cleared();

private:
    void connectToStore();

private:
    IMsgIDFilterStore *msgIDFilterStore;

};

/**
 * @}
 */

#endif /* MSGIDFILTERMODEL_H */
