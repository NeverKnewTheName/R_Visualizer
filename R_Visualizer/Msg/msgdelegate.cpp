#include "msgdelegate.h"

#include "msgmodel.h"
#include "msg.h"

#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>

#include <QDebug>

MsgDelegate::MsgDelegate(MsgTypeModel &msgTypeModel, IDModel &idModel, QWidget *parent)
    : QStyledItemDelegate(parent),
      msgTypeModel(msgTypeModel),
      idModel(idModel)
{

}

void MsgDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    int col = index.column();
    int row = index.row();
    QPixmap CurPixMap;

    if( col == MsgModel::COL_TIMESTAMP)
    {
        CurPixMap = MsgTimeStampPixMapStore.value(row);
        if(CurPixMap.isNull())
        {
//            UpdatePixmap(index);
        }
    }
    else if (col == MsgModel::COL_NAME)
    {
        CurPixMap = MsgIDPixMapStore.value(row);
        if(CurPixMap.isNull())
        {
//            UpdatePixmap(index);
        }
    }
    else if (col == MsgModel::COL_MESSAGE)
    {
        CurPixMap = MsgDataPixMapStore.value(row);
        if(CurPixMap.isNull())
        {
//            UpdatePixmap(index);
        }
    }
    //    int col = index.column();
    //    int row = index.row();
    //    QPixmap CurPixMap;
    //    QColor background = option.palette.color(
    //                option.palette.currentColorGroup(),
    //                (option.features & QStyleOptionViewItem::Alternate) ? QPalette::AlternateBase : QPalette::Base);
    //    QStringList dataPrint;
    //    QString toPrint = QString("");

    //    painter->save();

    //    //    QStyledItemDelegate::paint(painter, option, index);
    //    QStyleOptionViewItem opt = option;
    //    QStyledItemDelegate::initStyleOption(&opt, index);
    //    QRect rect = opt.rect;

    //    if( col == MsgModel::COL_TIMESTAMP)
    //    {
    //        CurPixMap = MsgTimeStampPixMapStore.value(row);
    //        if(CurPixMap.isNull())
    //        {
    //            CurPixMap = QPixmap(rect.size());
    //            CurPixMap.fill(background);
    //            QPainter MsgTimestampPainter(&CurPixMap);
    //            MsgTimestampPainter.setRenderHint(QPainter::TextAntialiasing);
    //            MsgTimestampPainter.drawText(
    //                        rect,
    //                        Qt::TextWordWrap |
    //                        Qt::AlignCenter,
    //                        index.data(Qt::DisplayRole).value<QString>()
    //                        );
    //            MsgTimeStampPixMapStore.replace(row,CurPixMap);
    //        }
    //    }
    //    else if (col == MsgModel::COL_NAME)
    //    {
    //        CurPixMap = MsgIDPixMapStore.value(row);
    //        if(CurPixMap.isNull())
    //        {
    //            MsgIDType id = index.data(Qt::UserRole +3).value<int>();
    //            if(!idModel.getNameToID(id).isEmpty())
    //            {
    //                idModel.paintID(opt, CurPixMap, id);
    //            }
    //            if(CurPixMap.isNull())
    //            {
    //                CurPixMap = QPixmap(rect.size());
    //                CurPixMap.fill(background);
    //                QPainter MsgIDPainter(&CurPixMap);
    //                MsgIDPainter.setRenderHint(QPainter::TextAntialiasing);
    //                MsgIDPainter.drawText(
    //                            rect,
    //                            Qt::TextWordWrap |
    //                            Qt::AlignCenter,
    //                            index.data(Qt::DisplayRole).value<QString>()
    //                            );
    //            }
    //            MsgIDPixMapStore.replace(row, CurPixMap);
    //        }
    //    }
    //    else if (col == MsgModel::COL_MESSAGE)
    //    {
    //        CurPixMap = MsgDataPixMapStore.value(row);
    //        if(CurPixMap.isNull())
    //        {
    //            MsgCodeType code = index.data(Qt::UserRole +3).value<int>();
    //            if(!msgTypeModel.getNameToCode(code).isEmpty())
    //            {
    //                msgTypeModel.paintMsgTypeRep(rect, code);
    //            }
    //            if(CurPixMap.isNull())
    //            {
    //                CurPixMap = QPixmap(rect.size());
    //                CurPixMap.fill(background);
    //                QPainter MsgDataPainter(&CurPixMap);
    //                MsgDataPainter.setRenderHint(QPainter::TextAntialiasing);
    //                MsgDataPainter.drawText(
    //                            rect,
    //                            Qt::TextWordWrap |
    //                            Qt::AlignCenter,
    //                            index.data(Qt::DisplayRole).value<QString>()
    //                            );
    //            }
    //            MsgDataPixMapStore.replace(row, CurPixMap);
    //        }
    //    }

    if(CurPixMap.isNull())
    {
        QStyledItemDelegate::paint(painter,option,index);
    }
    else
    {
        painter->drawPixmap(option.rect, CurPixMap);
    }
    painter->restore();
}

QSize MsgDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //    QSize result = QStyledItemDelegate::sizeHint(option, index);

    //    QPixmap MsgPixMap;
    //    QString UnqPxmpKey = index.model()->data(index, Qt::UserRole + 2).value<QString>();
    //    if(QPixmapCache::find(UnqPxmpKey,&MsgPixMap))
    //    {
    //        result.setHeight(MsgPixMap.size().height());
    //    }
    //    else
    //    {
    //        int nrOfLines = msgTypeModel.getNrLinesToCode(index.model()->data(index, Qt::UserRole + 2).value<int>());
    //        result.setHeight(result.height() + option.fontMetrics.height()*((nrOfLines>1) ? nrOfLines : 1 ));
    //        //result.setHeight(result.height() * ((nrOfLines>1) ? nrOfLines : 1 ));
    //    }

    int row = index.row();
    const QAbstractItemModel *model = index.model();
    return option.fontMetrics.boundingRect(
                option.rect,
                Qt::TextWordWrap,
                model->data(model->index(row,3)).toString()
                ).size();

    //    return result;
    //return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *MsgDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent,option,index);
}

void MsgDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    return QStyledItemDelegate::setEditorData(editor, index);
}

void MsgDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    return QStyledItemDelegate::setModelData(editor, model, index);
}

void MsgDelegate::UpdatePixmap(const QModelIndex &index)
{
    Q_UNUSED(index)
//    int col = index.column();
//    int row = index.row();

//    QPixmap CurPixMap;
//    QColor background = option.palette.color(
//                option.palette.currentColorGroup(),
//                (option.features & QStyleOptionViewItem::Alternate) ? QPalette::AlternateBase : QPalette::Base);

//    //    QStyledItemDelegate::paint(painter, option, index);
//    QStyleOptionViewItem opt = option;
//    QStyledItemDelegate::initStyleOption(&opt, index);
//    QRect rect = opt.rect;

//    switch(col)
//    {
//    case MsgModel::COL_MESSAGE:
//        CurPixMap = MsgDataPixMapStore.value(row);
//        if(CurPixMap.isNull())
//        {
//            MsgCodeType code = index.data(Qt::UserRole +3).value<int>();
//            if(!msgTypeModel.getNameToCode(code).isEmpty())
//            {
//                msgTypeModel.paintMsgTypeRep(rect, code);
//            }
//            if(CurPixMap.isNull())
//            {
//                CurPixMap = QPixmap(rect.size());
//                CurPixMap.fill(background);
//                QPainter MsgDataPainter(&CurPixMap);
//                MsgDataPainter.setRenderHint(QPainter::TextAntialiasing);
//                MsgDataPainter.drawText(
//                            rect,
//                            Qt::TextWordWrap |
//                            Qt::AlignCenter,
//                            index.data(Qt::DisplayRole).value<QString>()
//                            );
//            }
//            MsgDataPixMapStore.replace(row, CurPixMap);
//        }
//        //FALLTHROUGH -> if changed, the ID has to be repainted as well
//    case MsgModel::COL_NAME:
//        CurPixMap = MsgIDPixMapStore.value(row);
//        if(CurPixMap.isNull())
//        {
//            MsgIDType id = index.data(Qt::UserRole +3).value<int>();
//            if(!idModel.getNameToID(id).isEmpty())
//            {
//                idModel.paintID(opt, CurPixMap, id);
//            }
//            if(CurPixMap.isNull())
//            {
//                CurPixMap = QPixmap(rect.size());
//                CurPixMap.fill(background);
//                QPainter MsgIDPainter(&CurPixMap);
//                MsgIDPainter.setRenderHint(QPainter::TextAntialiasing);
//                MsgIDPainter.drawText(
//                            rect,
//                            Qt::TextWordWrap |
//                            Qt::AlignCenter,
//                            index.data(Qt::DisplayRole).value<QString>()
//                            );
//            }
//            MsgIDPixMapStore.replace(row, CurPixMap);
//        }
//        //FALLTHROUGH -> if MsgData changed, the Timestamp has to be repainted as well..
//    case MsgModel::COL_TIMESTAMP:
//        CurPixMap = MsgTimeStampPixMapStore.value(row);
//        if(CurPixMap.isNull())
//        {
//            CurPixMap = QPixmap(rect.size());
//            CurPixMap.fill(background);
//            QPainter MsgTimestampPainter(&CurPixMap);
//            MsgTimestampPainter.setRenderHint(QPainter::TextAntialiasing);
//            MsgTimestampPainter.drawText(
//                        rect,
//                        Qt::TextWordWrap |
//                        Qt::AlignCenter,
//                        index.data(Qt::DisplayRole).value<QString>()
//                        );
//            MsgTimeStampPixMapStore.replace(row,CurPixMap);
//        }
//    }
}

//void MsgDelegate::setMsgTypeModel(MsgTypeModel *msgTypeModel)
//{
//    this->msgTypeModel = msgTypeModel;
//}

//void MsgDelegate::setIDModel(IDModel *idModel)
//{
//    this->idModel = idModel;
//}

void MsgDelegate::commitAndCloseEditor()
{

}
