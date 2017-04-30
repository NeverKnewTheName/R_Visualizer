/**
 * @file MsgDataDelegate.h
 * @author Christian Neuberger
 * @date 2017-04-30
 * 
 * @brief Delegate for #MsgDataType
 */
#ifndef MSGDATADELEGATE_H
#define MSGDATADELEGATE_H

#include <QStyledItemDelegate>

#include "MsgDataType.h"

class IMsgDataMappingManager;

/**
 * @addtogroup MessageFieldDelegateGroup
 * 
 * @{
 */

/**
 * @brief The MsgDataDelegate
 */
class MsgDataDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MsgDataDelegate(
            IMsgDataMappingManager *msgDataMappingManager,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgDataDelegate();

    void paint(
            QPainter *painter,
            const QStyleOptionViewItem &option,
            const QModelIndex &index
            ) const Q_DECL_OVERRIDE;

    QSize sizeHint(
            const QStyleOptionViewItem &option,
            const QModelIndex &index
            ) const Q_DECL_OVERRIDE;

    QWidget *createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index
            ) const Q_DECL_OVERRIDE;

    void setEditorData(
            QWidget *editor,
            const QModelIndex &index
            ) const Q_DECL_OVERRIDE;

    void setModelData(
            QWidget *editor,
            QAbstractItemModel *model,
            const QModelIndex &index
            ) const Q_DECL_OVERRIDE;

public slots:
    void slt_MappingHasChanged(
            const IMsgDataMappingManager &msgDataMappingManager
            );

    void slt_CommitAndCloseEditor();

private:
    IMsgDataMappingManager *msgDataMappingManager;
};

/**
 * @}
 */

#endif /* MSGDATADELEGATE_H */
