#include "MsgDataFormatter.h"

#include "IMsg.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QVariant>
#include <QStringList>

#include <QDebug>

MsgDataFormatter::MsgDataFormatter(
        const QString &formatString,
        const QColor &defaultColor
        ) :
    formatString(formatString),
    defaultColor(defaultColor)
{
}

MsgDataFormatter::~MsgDataFormatter()
{
}

void MsgDataFormatter::setFormatString(
        const QString &formatString
        )
{
    this->formatString = formatString;
}

QString MsgDataFormatter::getFormatString() const
{
    return formatString;
}

void MsgDataFormatter::setDefaultColor(
        const QColor &defaultColor
        )
{
    this->defaultColor = defaultColor;
}

QColor MsgDataFormatter::getDefaultColor() const
{
    return defaultColor;
}

QString MsgDataFormatter::parseMsgDataToString(const IMsg &msgToParse) const
{
    const MsgDataType &msgData = msgToParse.getMsgData();

    QString formattedData(formatString);

    int dataSize = msgData.size();

    while(dataSize--)
    {
        QString dataTokenString("#Data%1#");
        formattedData.replace(dataTokenString.arg(dataSize),QString::number(msgData.at(dataSize).getPrimitiveData()));
    }

    QString regExPattern("#OP#\\((\\d+)#([\\+\\-\\*\\/%&|^]|(>>)|(<<))#(\\d+)\\)#\\/OP#");
    QRegularExpression operationParseRegEx(regExPattern);
    operationParseRegEx.setPatternOptions(QRegularExpression::DontCaptureOption);
    if(!operationParseRegEx.isValid())
    {
        qDebug() << operationParseRegEx.errorString();
        qDebug() << regExPattern;
    }
    QString operationString = QRegularExpressionMatch(operationParseRegEx.match(formattedData)).captured();

    while(!operationString.isEmpty())
    {
        QString parsedOperation = operationString;
        //qDebug() << "Operation to parse: " << parsedOperation;

        QVariant operationResult;
        parsedOperation.remove("#OP#(").remove(")#/OP#");
        //qDebug() << "Operation to parse: " << parsedOperation;

        QStringList operands = parsedOperation.split("#");
        //qDebug() << "Operands: " << operands;

        QString operation = operands.at(1);
        if(!operation.compare("+"))
        {
            operationResult.setValue(operands.first().toInt() + operands.last().toInt());
        }
        else if(!operation.compare("-"))
        {
            operationResult.setValue(operands.first().toInt() - operands.last().toInt());
        }
        else if(!operation.compare("*"))
        {
            operationResult.setValue(operands.first().toInt() * operands.last().toInt());
        }
        else if(!operation.compare("/"))
        {
            operationResult.setValue(operands.first().toInt() / operands.last().toInt());
        }
        else if(!operation.compare("%"))
        {
            operationResult.setValue(operands.first().toInt() % operands.last().toInt());
        }
        else if(!operation.compare("<<"))
        {
            operationResult.setValue(operands.first().toInt() << operands.last().toInt());
        }
        else if(!operation.compare(">>"))
        {
            operationResult.setValue(operands.first().toInt() >> operands.last().toInt());
        }
        else if(!operation.compare("&"))
        {
            operationResult.setValue(operands.first().toInt() & operands.last().toInt());
        }
        else if(!operation.compare("|"))
        {
            operationResult.setValue(operands.first().toInt() | operands.last().toInt());
        }
        else if(!operation.compare("^"))
        {
            operationResult.setValue(operands.first().toInt() ^ operands.last().toInt());
        }

        //qDebug() << "Operation Result: " << operationResult;

        formattedData.replace(operationString, operationResult.value<QString>());
        operationString = QRegularExpressionMatch(operationParseRegEx.match(formattedData)).captured();
    }

    // PARSE HEX
    QRegularExpression numberConversionRegEx(QString("#HEX#\\(\\d+\\)#\\/HEX#"));
    QString numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
    while(!numConvString.isEmpty())
    {
        QString parsedNumber = numConvString;
        parsedNumber.remove(QString("#HEX#(")).remove(QString(")#/HEX#"));
        formattedData.replace(numConvString,QString("0x%1").arg(parsedNumber.toInt(),0,16));
        numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
    }

    // PARSE OCT
    numberConversionRegEx.setPattern(QString("#OCT#\\(\\d+\\)#\\/OCT#"));
    numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
    while(!numConvString.isEmpty())
    {
        QString parsedNumber = numConvString;
        parsedNumber.remove(QString("#OCT#(")).remove(QString(")#/OCT#"));
        formattedData.replace(numConvString,QString("0x%1").arg(parsedNumber.toInt(),0,8));
        numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
    }

    // PARSE BIN
    numberConversionRegEx.setPattern(QString("#BIN#\\(\\d+\\)#\\/BIN#"));
    numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
    while(!numConvString.isEmpty())
    {
        QString parsedNumber = numConvString;
        parsedNumber.remove(QString("#BIN#(")).remove(QString(")#/BIN#"));
        formattedData.replace(numConvString,QString("0x%1").arg(parsedNumber.toInt(),0,2));
        numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
    }

    return formattedData;
}

QColor MsgDataFormatter::parseMsgDataToColor(const IMsg &msgToParse) const
{
    return defaultColor;
}
