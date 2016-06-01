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
        QString msgString = this->msgTypeModel->getMessageToCode(msgData.code);
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
            // format the message according to the retrieved format string
            QString formatString = msgString;
            QString formattedMessage = formatString;
            formattedMessage.replace("#Data0#", QString::number(msgData.data0));
            formattedMessage.replace("#Data1#", QString::number(msgData.data1));
            formattedMessage.replace("#Data2#", QString::number(msgData.data2));
            formattedMessage.replace("#Data3#", QString::number(msgData.data3));
            formattedMessage.replace("#Data4#", QString::number(msgData.data4));
            formattedMessage.replace("#Data5#", QString::number(msgData.data5));
            formattedMessage.replace("#Data6#", QString::number(msgData.data6));
            // parse operations form string
            //QRegularExpression opParse(QString("#OP#\\((\\d\\.?\\d*)#.*#(\\d\\.?\\d*)\\)#\\/OP#"));
            QRegularExpression opParse(QString("#OP#\\((\\d\\.?\\d*)#([+-/*%&|^]|(>>)|(<<))#(\\d\\.?\\d*)\\)#\\/OP#"));
            opParse.setPatternOptions(QRegularExpression::DontCaptureOption); // only capture the whole operation
            //QStringList opList = QRegularExpressionMatch(opParse.match(formattedMessage)).capturedTexts(); // build a string list from the operations
            QString opString = QRegularExpressionMatch(opParse.match(formattedMessage)).captured();
            while(!opString.isEmpty())
            {
                QString parsedOperation = opString;
                QVariant opResult;
                parsedOperation.replace("#OP#(","").replace(")#/OP#","");
                QStringList operands = parsedOperation.split("#");
                if(!operands.at(1).compare("+"))
                {
                    opResult.setValue(operands.at(0).toInt() + operands.at(2).toInt());
                }
                else if(!operands.at(1).compare("-"))
                {
                    opResult.setValue(operands.at(0).toInt() - operands.at(2).toInt());
                }
                else if(!operands.at(1).compare("*"))
                {
                    opResult.setValue(operands.at(0).toInt() * operands.at(2).toInt());
                }
                else if(!operands.at(1).compare("/"))
                {
                    opResult.setValue(operands.at(0).toInt() / operands.at(2).toInt());
                }
                else if(!operands.at(1).compare("%"))
                {
                    opResult.setValue(operands.at(0).toInt() % operands.at(2).toInt());
                }
                else if(!operands.at(1).compare(">>"))
                {
                    opResult.setValue(operands.at(0).toInt() >> operands.at(2).toInt());
                }
                else if(!operands.at(1).compare("<<"))
                {
                    opResult.setValue(operands.at(0).toInt() << operands.at(2).toInt());
                }
                else if(!operands.at(1).compare("&"))
                {
                    opResult.setValue(operands.at(0).toInt() & operands.at(2).toInt());
                }
                else if(!operands.at(1).compare("|"))
                {
                    opResult.setValue(operands.at(0).toInt() | operands.at(2).toInt());
                }
                else if(!operands.at(1).compare("^"))
                {
                    opResult.setValue(operands.at(0).toInt() ^ operands.at(2).toInt());
                }

                formattedMessage.replace(opString,QString::number(opResult.value<int>())); //replace operation tokens with the result
                opString = QRegularExpressionMatch(opParse.match(formattedMessage)).captured();
            }
            // Parse HEX conversions
            opParse.setPattern(QString("#HEX#\\(\\d+\\)#\\/HEX#"));
            opString = QRegularExpressionMatch(opParse.match(formattedMessage)).captured();
            while(!opString.isEmpty())
            {
                QString parsedNumber = opString;
                parsedNumber.replace(QString("#HEX#("),QString("")).replace(QString(")#/HEX#"),QString(""));
                formattedMessage.replace(opString,QString("0x%1").arg(parsedNumber.toInt(),0,16)); //replace operation tokens with the result
                //opList = QRegularExpressionMatch(opParse.match(formattedMessage)).capturedTexts();
                opString = QRegularExpressionMatch(opParse.match(formattedMessage)).captured();
            }
            // Parse OCT conversions
            opParse.setPattern(QString("#OCT#\\(\\d+\\)#\\/OCT#"));
            opString = QRegularExpressionMatch(opParse.match(formattedMessage)).captured();
            while(!opString.isEmpty())
            {
                QString parsedNumber = opString;
                parsedNumber.replace(QString("#OCT#("),QString("")).replace(QString(")#/OCT#"),QString(""));
                formattedMessage.replace(opString,QString("0%1").arg(parsedNumber.toInt(),0,8)); //replace operation tokens with the result
                //opList = QRegularExpressionMatch(opParse.match(formattedMessage)).capturedTexts();
                opString = QRegularExpressionMatch(opParse.match(formattedMessage)).captured();
            }
            // Parse BIN conversions
            opParse.setPattern(QString("#BIN#\\(\\d+\\)#\\/BIN#"));
            opString = QRegularExpressionMatch(opParse.match(formattedMessage)).captured();
            while(!opString.isEmpty())
            {
                QString parsedNumber = opString;
                parsedNumber.replace(QString("#BIN#("),QString("")).replace(QString(")#/BIN#"),QString(""));
                formattedMessage.replace(opString,QString("%1").arg(parsedNumber.toInt(),0,2)); //replace operation tokens with the result
                //opList = QRegularExpressionMatch(opParse.match(formattedMessage)).capturedTexts();
                opString = QRegularExpressionMatch(opParse.match(formattedMessage)).captured();
            }


            dataPrint.append(formattedMessage.split("\n"));
        }
    }

    // check if the row containing the item is selected and adapt the background accordingly
    if(option.state & QStyle::State_Selected)
    {
        background = background.darker();
    }
    // draw background
    painter->fillRect(option.rect, background);
    //painter->drawRect(option.rect.);
    int nrLines = dataPrint.size();
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
    int nrOfLines = this->msgTypeModel->getNrLinesToCode(index.model()->data(index, Qt::UserRole + 2).value<int>());
    result.setHeight(result.height() + option.fontMetrics.height()*((nrOfLines>1) ? nrOfLines : 1 ));
    //result.setHeight(result.height() * ((nrOfLines>1) ? nrOfLines : 1 ));
    return result;
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
