#include "SysOverviewObjectTriggerDSLEvaluator.h"

#include "IMsg.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QVariant>
#include <QStringList>

#include <QDebug>


SysOverviewObjectTriggerDSLEvaluator::SysOverviewObjectTriggerDSLEvaluator(
        const MessageTypeIdentifier &msgType,
        const QString &formatString
        ) :
    msgType(msgType),
    formatString(formatString)
{

}

SysOverviewObjectTriggerDSLEvaluator::~SysOverviewObjectTriggerDSLEvaluator()
{

}


ISysOverviewObjectTriggerEvaluator::EvaluatorType SysOverviewObjectTriggerDSLEvaluator::getType() const
{
    return ISysOverviewObjectTriggerEvaluator::EvaluatorType_DSLEvaluator;
}

MessageTypeIdentifier SysOverviewObjectTriggerDSLEvaluator::getMsgType() const
{
    return msgType;
}

void SysOverviewObjectTriggerDSLEvaluator::setMsgType(
        const MessageTypeIdentifier &msgType
        )
{
    this->msgType = msgType;
}

bool SysOverviewObjectTriggerDSLEvaluator::evaluate(
        const IMsg &msgToEvaluate
        ) const
{
    if(msgToEvaluate.getMsgType() != msgType)
    {
        return false;
    }
    else
    {

        const MsgDataType &msgData = msgToEvaluate.getMsgData();

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

        int numFormat = 10;
        // PARSE HEX
        QRegularExpression numberConversionRegEx(QString("#HEX#\\(\\d+\\)#\\/HEX#"));
        QString numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
        while(!numConvString.isEmpty())
        {
            QString parsedNumber = numConvString;
            parsedNumber.remove(QString("#HEX#(")).remove(QString(")#/HEX#"));
            formattedData.replace(numConvString,QString("0x%1").arg(parsedNumber.toInt(),0,16));
            numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
            numFormat = 16;
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
            numFormat = 8;
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
            numFormat = 2;
        }

        bool ok;
        const int result = formattedData.toInt(&ok,numFormat);

        if(ok)
        {
            return result;
        }
        else
        {
            return false;
        }
    }
}

QString SysOverviewObjectTriggerDSLEvaluator::evaluateToString(
        const IMsg &msgToEvaluate
        ) const
{

    if(msgToEvaluate.getMsgType() != msgType)
    {
        return QString();
    }
    else
    {

        const MsgDataType &msgData = msgToEvaluate.getMsgData();

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

        int numFormat = 10;
        // PARSE HEX
        QRegularExpression numberConversionRegEx(QString("#HEX#\\(\\d+\\)#\\/HEX#"));
        QString numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
        while(!numConvString.isEmpty())
        {
            QString parsedNumber = numConvString;
            parsedNumber.remove(QString("#HEX#(")).remove(QString(")#/HEX#"));
            formattedData.replace(numConvString,QString("0x%1").arg(parsedNumber.toInt(),0,16));
            numConvString = QRegularExpressionMatch(numberConversionRegEx.match(formattedData)).captured();
            numFormat = 16;
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
            numFormat = 8;
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
            numFormat = 2;
        }

        return formattedData;
    }
}

QString SysOverviewObjectTriggerDSLEvaluator::getFormatString() const
{
    return formatString;
}

void SysOverviewObjectTriggerDSLEvaluator::setFormatString(const QString &value)
{
    formatString = value;
}
