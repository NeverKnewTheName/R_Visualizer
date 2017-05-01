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
    connect(
            msgDataMappingManager,
            &IMsgDataMappingManager::sgnl_MsgDataMappingManagerChanged,
            this,
            &MsgDataDelegate::slt_MappingHasChanged
           );
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
    QStyledItemDelegate::paint(painter,option,index);
    const MsgDataType &msgData = index.data(Qt::UserRole).value<MsgDataType>();

    //QString alias = msgDataMappingManager->getMsgDataFormatter();

    //if(alias.isEmpty())
    //{
        //alias = static_cast<QString>(msgData);
    //}
//
    //const QColor &colorRep = msgDataMappingManager->getColorToMsgData(msgData);
//
    //painter->save();
//
    //painter->setFont(option.font);
    //painter->setRenderHint(QPainter::TextAntialiasing);
    //painter->fillRect(
            //option.rect,
            //(
                    //(option.state & QStyle::State_Selected) ?
                        //option.palette.highlight() :
                //(option.features & QStyleOptionViewItem::Alternate) ?
                //colorRep.darker(100) :
                //colorRep
            //)
            //);
//
    //painter->drawText(
            //option.rect,
            //Qt::TextWordWrap | Qt::AlignLeft,
            //alias
            //);
//
    //painter->restore();
}

QSize MsgDataDelegate::sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
    QStyledItemDelegate::sizeHint(option,index);
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
