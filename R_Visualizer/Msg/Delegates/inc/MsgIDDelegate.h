/**
 * @file MsgIDDelegate.h
 * @author Christian Neuberger
 * @date 2017-04-30
 * 
 * @brief Delegate for #MsgIDType
 */
#ifndef MSGIDDELEGATE_H
#define MSGIDDELEGATE_H

#include <QStyledItemDelegate>

#include "MsgIDType.h"

class IMsgIDMappingManager;


/**
 * @defgroup MessageFieldDelegateGroup  Message Field Delegates
 * @ingroup MessageGroup
 * 
 * @{
 */

/**
 * @brief The MsgIDDelegate
 */
class MsgIDDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MsgIDDelegate(
            IMsgIDMappingManager *msgIDMappingManager,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgIDDelegate();

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
            const IMsgIDMappingManager &msgIDMappingManager
            );

    void slt_CommitAndCloseEditor();

private:
    IMsgIDMappingManager *msgIDMappingManager;


    // QAbstractItemDelegate interface
public:
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

/**
 * @}
 */
#endif /* MSGIDDELEGATE_H */
