#include "MsgDataDelegate.h"

#include "IMsgDataMappingManager.h"

#include <QPainter>

MsgDataDelegate::MsgDataDelegate(
        IMsgDataMappingManager *msgDataMappingManager,
        QObject *parent
        ) :
    QStyledItemDelegate(parent),
    msgDataMappingManager(msgDataMappingManager)
{
}

MsgDataDelegate::~MsgDataDelegate()
{
}

void MsgDataDelegate::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
}

QSize MsgDataDelegate::sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
}

QWidget *MsgDataDelegate::createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index
        ) const
{
}

void MsgDataDelegate::setEditorData(
        QWidget *editor,
        const QModelIndex &index
        ) const
{
}

void MsgDataDelegate::setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex &index
        ) const
{
}

void MsgDataDelegate::slt_MappingHasChanged(
        const IMsgDataMappingManager &msgDataMappingManager
        )
{
}

void MsgDataDelegate::slt_CommitAndCloseEditor()
{
}
