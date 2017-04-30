#include "MsgCodeDelegate.h"

#include "IMsgCodeMappingManager.h"

#include <QPainter>

MsgCodeDelegate::MsgCodeDelegate(
        IMsgCodeMappingManager *msgCodeMappingManager,
        QObject *parent
        ) :
    QStyledItemDelegate(parent),
    msgCodeMappingManager(msgCodeMappingManager)
{
}

MsgCodeDelegate::~MsgCodeDelegate()
{
}

void MsgCodeDelegate::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
}

QSize MsgCodeDelegate::sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
}

QWidget *MsgCodeDelegate::createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index
        ) const
{
}

void MsgCodeDelegate::setEditorData(
        QWidget *editor,
        const QModelIndex &index
        ) const
{
}

void MsgCodeDelegate::setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex &index
        ) const
{
}

void MsgCodeDelegate::slt_MappingHasChanged(
        const IMsgCodeMappingManager &msgCodeMappingManager
        )
{
}

void MsgCodeDelegate::slt_CommitAndCloseEditor()
{
}
