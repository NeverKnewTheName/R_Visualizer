#include "MsgDataFormatter.h"

#include "IMsg.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QVariant>
#include <QStringList>

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

    QRegularExpression operationParseRegEx(QString("#OP#\\((\\d\\.\\.?\\d*)#([+-*/%&|^]|(>>)|(<<))#(\\d\\.?\\d*)\\)#\\/OP#"));
    operationParseRegEx.setPatternOptions(QRegularExpression::DontCaptureOption);
    QString operationString = QRegularExpressionMatch(operationParseRegEx.match(formattedData)).captured();

    while(!operationString.isEmpty())
    {
        QString parsedOperation = operationString;
        QVariant operationResult;
        parsedOperation.remove("#OP#(").remove(")#OP#");
        QStringList operands = parsedOperation.split("#");

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

        formattedData.replace(operationString, operationResult.value<QString>());
        operationString = QRegularExpressionMatch(operationParseRegEx.match(formattedData)).captured();
    }

    return formattedData;
}

QColor MsgDataFormatter::parseMsgDataToColor(const IMsg &msgToParse) const
{
    return defaultColor;
}
