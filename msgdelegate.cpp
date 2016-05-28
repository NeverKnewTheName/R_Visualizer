#include "msgdelegate.h"

#include "msgmodel.h"
#include "msg.h"

#include <QPainter>

MsgDelegate::MsgDelegate(MsgTypeModel *msgTypeModel, IDModel *idModel, QWidget *parent)
    : QStyledItemDelegate(parent),
      msgTypeModel(msgTypeModel),
      idModel(idModel)
{

}

void MsgDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();
    QColor background;
    QString dataPrint;

    if( col == MsgModel::COL_TIMESTAMP)
    {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    else if (col == MsgModel::COL_NAME)
    {
        int id = index.model()->data(index, Qt::DisplayRole).value<int>();
        background = (this->idModel->getColorToID(id));

        dataPrint = this->idModel->getNameToID(id);
        if(dataPrint.isEmpty())
        {
            // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
            dataPrint =  QString("0x%1").arg(id/*decimal*/, 4/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
        }
    }
    else if (col == MsgModel::COL_MESSAGE)
    {
        MsgDataT msgData = index.model()->data(index, Qt::UserRole + 1).value<MsgDataT>();
        background = this->msgTypeModel->getColorToCode(msgData.code);

        painter->fillRect(option.rect, background);

        QString codeName = this->msgTypeModel->getMessageToCode(msgData.code);
        if(codeName.isEmpty())
        {
            dataPrint.append(QString("Code:\t"));
            dataPrint.append(QString("0x%1").arg(msgData.code/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/) );
        }
        else
        {
            dataPrint.append(QString("Code:\t"));
            dataPrint.append(codeName);
        }
        dataPrint.append(QString("\n"));
        dataPrint.append(QString("Message:\t0x%1%2%3%4%5%6%7")
                         .arg(msgData.data0/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                         .arg(msgData.data1/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                         .arg(msgData.data2/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                         .arg(msgData.data3/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                         .arg(msgData.data4/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                         .arg(msgData.data5/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                         .arg(msgData.data6/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/));

    }


    if(option.state & QStyle::State_Selected)
    {
        background = background.darker();
    }
    painter->fillRect(option.rect, background);
    painter->drawText(option.rect, Qt::AlignLeft/* | Qt::AlignBottom*/, dataPrint);

    //QStyledItemDelegate::paint(painter, option, index);
}

QSize MsgDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    //result.setHeight(result.height()*index.model()->data(index, Qt::UserRole + 2 ));
    return result;
    //return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *MsgDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void MsgDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void MsgDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void MsgDelegate::setMsgTypeModel(MsgTypeModel *msgTypeModel)
{
    this->msgTypeModel = msgTypeModel;
}

void MsgDelegate::commitAndCloseEditor()
{

}
