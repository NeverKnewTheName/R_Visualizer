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
    QColor background = option.palette.color(
                option.palette.currentColorGroup(),
                (option.features & QStyleOptionViewItem::Alternate) ? QPalette::AlternateBase : QPalette::Base);
    QStringList dataPrint;

    QStyledItemDelegate::paint(painter, option, index);

    if( col == MsgModel::COL_TIMESTAMP)
    {
        dataPrint.append(index.model()->data(index, Qt::DisplayRole).value<QString>());
    }
    else if (col == MsgModel::COL_NAME)
    {
        int id = index.model()->data(index, Qt::DisplayRole).value<int>();
        QColor itemBackground = this->idModel->getColorToID(id);
        if(itemBackground.isValid())
        {
            if(option.features & QStyleOptionViewItem::Alternate)
            {
                background = itemBackground.darker(110);
            }
            else
            {
                background = itemBackground;
            }
        }

        QString idName = this->idModel->getNameToID(id);

        if(idName.isEmpty())
        {
            // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
            idName =  QString("0x%1").arg(id/*decimal*/, 4/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
        }
        dataPrint.append(idName);
    }
    else if (col == MsgModel::COL_MESSAGE)
    {
        // Retrieve MsgData structure from the message
        Msg *msg = static_cast<Msg*>(index.model()->data(index, Qt::UserRole + 1).value<void*>());
        quint16 code = msg->getCode();
        PMsgDataStruc msgData = msg->getData();
        // Get color for the background
        QColor itemBackground = this->msgTypeModel->getColorToCode(code);
        if(itemBackground.isValid())
        {
            if(option.features & QStyleOptionViewItem::Alternate)
            {
                background = itemBackground.darker(110);
            }
            else
            {
                background = itemBackground;
            }
        }
        // Get the name of the code included in the message
        // returns an empty string if no name is specified or if there is no netry in the MsgType model
        QString codeName = this->msgTypeModel->getNameToCode(code);
        if(codeName.isEmpty())
        {
            // There is no name specified or there is no entry in the MsgType model
            // Standard formatting for the code as hex
            codeName = QString("Code:\t0x%1").arg(code/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
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
        QString msgString = this->msgTypeModel->getMessageToCode(code);
        if(msgString.isEmpty())
        {
            // Craft a standard Message
            msgString = QString("Message:\t%1")
                    .arg(msg->getDataAsString());
            dataPrint.append(msgString);
        }
        else
        {
            // format the message according to the retrieved format string
            QString formatString = msgString;
            QString formattedMessage = formatString;
            QRegularExpression dataRE(QString("(#Data(\\d*)#)"));
            QRegularExpressionMatch dataMatch = dataRE.match(formattedMessage);
            while(dataMatch.hasMatch())
            {
                unsigned int dataIndex = dataMatch.captured(1).toInt();
                int num = 0;

                if(dataIndex < msgData->DataSizeInBytes)
                    num = msgData->DataBytes.at(dataIndex);
                else
                    qDebug() << __FUNCTION__ << "Index out of range!";

                formattedMessage.replace(QString("%1").arg(dataMatch.captured(0)), QString::number(num));
                dataMatch = dataRE.match(formattedMessage);
            }

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
        background = option.palette.color(option.palette.currentColorGroup(), QPalette::Highlight);
    }
    // draw background
    painter->fillRect(option.rect, background);
    //painter->drawRect(option.rect.);
    int nrLines = dataPrint.size();
    int linesPrinted = 0;
    int left = option.rect.left() + 2;
    int top = option.rect.top();
    int width = option.rect.width();
    int height = option.rect.height()/nrLines;
    for( const auto &line : dataPrint)
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
    //emit sizeHintChanged(index);
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
