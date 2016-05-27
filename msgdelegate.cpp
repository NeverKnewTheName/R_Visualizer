#include "msgdelegate.h"
#include "msg.h"

#include <QPainter>

MsgDelegate::MsgDelegate(MsgTypeModel *msgTypeModel, QWidget *parent) : QStyledItemDelegate(parent), msgTypeModel(msgTypeModel)
{

}

void MsgDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    MsgDataT msgData = index.model()->data(index, Qt::UserRole + 1).value<MsgDataT>();
    QColor background(this->msgTypeModel->getColorToCode(msgData.code));

    if(option.state & QStyle::State_Selected)
    {
        background.darker();
    } else {

    }

    painter->fillRect(option.rect, background);
    QString dataPrint;
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
