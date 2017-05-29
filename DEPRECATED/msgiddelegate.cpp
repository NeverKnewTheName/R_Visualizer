#include "msgiddelegate.h"

#include "msgmodel.h"
#include "idmodel.h"

#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>

#include <QDebug>

MsgIDDelegate::MsgIDDelegate(const IDModel &idModel, QWidget *parent) :
    QStyledItemDelegate(parent),
    idModel(idModel),
    MsgIDPixMapStore(100),
    relatedColumnWidth(100),
    relatedColumnHeight(50)
{
}

void MsgIDDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    const MsgIDType MsgID = index.data(Qt::UserRole).value<MsgIDType>();
    painter->save();

    if(!idModel.contains(MsgID))
    {
        QStyledItemDelegate::paint(painter,option,index);
    }
    else
    {
        /* idModel.paintID(painter, option, MsgID); */

    }
    painter->restore();
}

QSize MsgIDDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *MsgIDDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent,option,index);
}

void MsgIDDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    return QStyledItemDelegate::setEditorData(editor, index);
}

void MsgIDDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    return QStyledItemDelegate::setModelData(editor, model, index);
}

void MsgIDDelegate::UpdatePixmap(const QModelIndex &index)
{
    Q_UNUSED(index)
//    if(!index.isValid())
//        return;
//    if(index.column() != MsgModel::COL_NAME)
//        return;

//    int row = index.row();
//    QPixmap CurPixMap = MsgIDPixMapStore.value(row);

//    QRect rect = QRect(0,0,relatedColumnWidth,relatedColumnHeight);

//    if(rect.isNull())
//    {
//        return;
//    }

//    MsgIDType id = index.data(Qt::UserRole +3).value<int>();
//    if(!idModel.getNameToID(id).isEmpty())
//    {
//        idModel.paintID(rect, CurPixMap, id);
//    }
//    if(CurPixMap.isNull())
//    {
//        CurPixMap = QPixmap(rect.size());
//        CurPixMap.fill(Qt::white);
//        QPainter MsgIDPainter(&CurPixMap);
//        MsgIDPainter.setRenderHint(QPainter::TextAntialiasing);
//        MsgIDPainter.drawText(
//                    rect,
//                    Qt::TextWordWrap |
//                    Qt::AlignCenter,
//                    index.data(Qt::DisplayRole).value<QString>()
//                    );
//    }
//    MsgIDPixMapStore.replace(row, CurPixMap);
}

void MsgIDDelegate::columWidthChanged(int newWidth)
{
    relatedColumnWidth = newWidth;
}

void MsgIDDelegate::columHeightChanged(int newHeight)
{

}

void MsgIDDelegate::commitAndCloseEditor()
{

}
