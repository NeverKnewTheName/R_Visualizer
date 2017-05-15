/**
 * @file MsgCodeDelegate.h
 * @author Christian Neuberger
 * @date 2017-04-30
 * 
 * @brief Delegate for #MsgCodeType
 */
#ifndef MSGCODEDELEGATE_H
#define MSGCODEDELEGATE_H

#include <QStyledItemDelegate>

#include "MsgCodeType.h"

class IMsgCodeMappingManager;

/**
 * @addtogroup MessageFieldDelegateGroup
 * 
 * @{
 */

/**
 * @brief The MsgCodeDelegate
 */
class MsgCodeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MsgCodeDelegate(
            IMsgCodeMappingManager *msgCodeMappingManager,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeDelegate();

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
            const IMsgCodeMappingManager &msgCodeMappingManager
            );

    void slt_CommitAndCloseEditor();

private:
    IMsgCodeMappingManager *msgCodeMappingManager;
};

/**
 * @}
 */
#endif /* MSGCODEDELEGATE_H */
