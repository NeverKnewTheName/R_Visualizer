#include "msgdatadelegate.h"

#include "msgmodel.h"
#include "msgtypemodel.h"
#include "msg.h"

#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>

#include <QTableView>
#include <QRect>

#include <QDebug>

MsgDataDelegate::MsgDataDelegate(MsgTypeModel &msgTypeModel, QWidget *parent) :
    QStyledItemDelegate(parent),
    msgTypeModel(msgTypeModel),
    MsgDataPixMapStore(100),
    relatedColumnWidth(100),
    relatedColumnHeight(50)
{
    //    connect(this, &MsgDataDelegate::MustUpdatePixmapForIndex, this, &MsgDataDelegate::UpdatePixmap, Qt::QueuedConnection);
}

void MsgDataDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    int row = index.row();
    QPixmap CurPixMap = MsgDataPixMapStore.value(row);

    painter->save();

    if(CurPixMap.isNull())
    {
        //emit MustUpdatePixmapForIndex(option, index);
        QStyledItemDelegate::paint(painter,option,index);
    }
    else
    {
        painter->drawPixmap(option.rect, CurPixMap);
    }

    painter->restore();
}

QSize MsgDataDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPixmap CurPixMap = MsgDataPixMapStore.value(index.row());
    if(CurPixMap.isNull())
        return QStyledItemDelegate::sizeHint(option, index);

    return CurPixMap.size();
}

QWidget *MsgDataDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent,option,index);
}

void MsgDataDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    return QStyledItemDelegate::setEditorData(editor, index);
}

void MsgDataDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    return QStyledItemDelegate::setModelData(editor, model, index);
}

void MsgDataDelegate::UpdatePixmap(const QModelIndex &index)
{
    if(!index.isValid())
        return;
    if(index.column() != MsgModel::COL_MESSAGE)
        return;

    int row = index.row();
    QPixmap CurPixMap = MsgDataPixMapStore.value(row);

    QRect rect = QRect(0,0,relatedColumnWidth,relatedColumnHeight);

    if(rect.isNull())
    {
        return;
    }

    MsgCodeType/*ToDO MsgCodeType*/ code = index.data(Qt::UserRole +3).value<int>();
    if(!msgTypeModel.getNameToCode(code).isEmpty())
    {
        msgTypeModel.paintMsgTypeRep(rect, CurPixMap, code);
    }
    if(CurPixMap.isNull())
    {
        CurPixMap = QPixmap(rect.size());
        CurPixMap.fill(Qt::white);
        QPainter MsgDataPainter(&CurPixMap);
        MsgDataPainter.setRenderHint(QPainter::TextAntialiasing);
        MsgDataPainter.drawText(
                    rect,
                    Qt::TextWordWrap |
                    Qt::AlignCenter,
                    index.data(Qt::DisplayRole).value<QString>()
                    );
    }
    MsgDataPixMapStore.replace(row, CurPixMap);
}

void MsgDataDelegate::columWidthChanged(int newWidth)
{
    relatedColumnWidth = newWidth;
}
void MsgDataDelegate::columHeightChanged(int newHeight)
{
    relatedColumnHeight = newHeight;
}

void MsgDataDelegate::commitAndCloseEditor()
{

}
