#include "msgdelegate.h"

#include "msgmodel.h"
#include "msg.h"

#include <QPainter>

#include <QDebug>

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
    QStringList dataPrint;

    if( col == MsgModel::COL_TIMESTAMP)
    {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    else if (col == MsgModel::COL_NAME)
    {
        int id = index.model()->data(index, Qt::DisplayRole).value<int>();
        background = (this->idModel->getColorToID(id));

        QString codeName = this->idModel->getNameToID(id);

        if(codeName.isEmpty())
        {
            // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
            codeName =  QString("0x%1").arg(id/*decimal*/, 4/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
        }
        dataPrint.append(codeName);
    }
    else if (col == MsgModel::COL_MESSAGE)
    {
        // Retrieve MsgData structure from the message
        MsgDataT msgData = index.model()->data(index, Qt::UserRole + 1).value<MsgDataT>();
        // Get color for the background
        background = this->msgTypeModel->getColorToCode(msgData.code);

        // Get the name of the code included in the message
        // returns an empty string if no name is specified or if there is no netry in the MsgType model
        QString codeName = this->msgTypeModel->getNameToCode(msgData.code);
        if(codeName.isEmpty())
        {
            // There is no name specified or there is no entry in the MsgType model
            // Standard formatting for the code as hex
            codeName = QString("Code:\t0x%1").arg(msgData.code/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
        }
        else
        {
            // Print the retrieved name
            codeName = QString("Code:\t") + codeName;
            //            dataPrint.append(QString("Code:\t"));
            //            dataPrint.append(codeName);
        }
        dataPrint.append(codeName);
        // end code line
        //dataPrint.append(QString("\n"));
        QString msgString = this->msgTypeModel->getMessageToCode(msgData.code, msgData);
        if(msgString.isEmpty())
        {
            // Craft a standard Message
            msgString = QString("Message:\t0x%1%2%3%4%5%6%7")
                    .arg(msgData.data0/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                    .arg(msgData.data1/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                    .arg(msgData.data2/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                    .arg(msgData.data3/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                    .arg(msgData.data4/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                    .arg(msgData.data5/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/)
                    .arg(msgData.data6/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
            dataPrint.append(msgString);
        }
        else
        {
            // Print the retrieved formatted message
            //qDebug() << "Formatted message: " << msgString;
            dataPrint.append(msgString.split("\n"));
        }
    }

    // check if the row containing the item is selected and adapt the background accordingly
    if(option.state & QStyle::State_Selected)
    {
        background = background.darker();
    }
    // draw background
    painter->fillRect(option.rect, background);
    int nrLines = dataPrint.size();
    //qDebug() << "Lines to print: " << nrLines;
    int linesPrinted = 0;
    int left = option.rect.left();
    int top = option.rect.top();
    int width = option.rect.width();
    int height = option.rect.height()/nrLines;
    for( auto &line : dataPrint)
    {
        // print text
        painter->drawText(
                    QRect(
                        left,
                        top+(linesPrinted*height),
                        width,
                        height
                        ),
                    Qt::AlignLeft/* | Qt::AlignBottom*/,
                    line);
        linesPrinted++;
    }
    //QStyledItemDelegate::paint(painter, option, index);
}

QSize MsgDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    qDebug() << "RESIZE HINT";
    qDebug() << result.height();
    int nrOfLines = this->msgTypeModel->getNrLinesToCode(index.model()->data(index, Qt::UserRole + 2).value<int>());
    result.setHeight(result.height() + option.fontMetrics.height()*((nrOfLines>1) ? nrOfLines : 1 ));
    //result.setHeight(result.height() * ((nrOfLines>1) ? nrOfLines : 1 ));
    qDebug() << result.height();
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

void MsgDelegate::setIDModel(IDModel *idModel)
{
    this->idModel = idModel;
}

void MsgDelegate::commitAndCloseEditor()
{

}
