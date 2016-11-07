#include "msgparser.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QDebug>

MsgParser::MsgParser(QString StringPattern) :
    StringPattern(StringPattern)
{
    // format the message according to the retrieved format string
    QString formattedString = StringPattern;
    // parse operations form string
    QRegularExpression opParse(QString("(#O(\\d+)##((?:D)|(?:V)|(?:R))(\\d+)##((?:D)|(?:V)|(?:R))(\\d+)##\\/O\\2#)"));
    //opParse.setPatternOptions(QRegularExpression::DontCaptureOption); // only capture the whole operation
    QRegularExpressionMatch FormatStringMatch = opParse.match(formattedString);

    while(FormatStringMatch.hasMatch())
    {
        Operation op;

        // Operation to perform
        op.opType = static_cast<OperatorToken>(FormatStringMatch.captured(2).toInt());
        // Operand 1
        // Type
        if(FormatStringMatch.captured(3).compare("D") == 0) // Message data field
        {
            op.OperandOne.DataType = DataFieldToken;
        }
        else if(FormatStringMatch.captured(3).compare("V") == 0) // Value
        {
            op.OperandOne.DataType = ValueToken;
        }
        else if(FormatStringMatch.captured(3).compare("R") == 0) // Result of preceding operation
        {
            op.OperandOne.DataType = ResultOfOperationToken;
        }
        op.OperandOne.DataValue = FormatStringMatch.captured(4).toInt();;
        // Operand 2
        // Type
        if(FormatStringMatch.captured(5).compare("D") == 0) // Message data field
        {
            op.OperandTwo.DataType = DataFieldToken;
        }
        else if(FormatStringMatch.captured(5).compare("V") == 0) // Value
        {
            op.OperandTwo.DataType = ValueToken;
        }
        else if(FormatStringMatch.captured(5).compare("R") == 0) // Result of preceding operation
        {
            op.OperandTwo.DataType = ResultOfOperationToken;
        }
        op.OperandTwo.DataValue = FormatStringMatch.captured(6).toInt();

        formattedString.replace(FormatStringMatch.capturedStart(0),FormatStringMatch.capturedLength(0),QString("#R%1#").arg(OperationStore.size())); //replace operation with the according result token
        OperationStore.append(op);

        FormatStringMatch = opParse.match(formattedString);
    }

    // parse remaining result/value form string
    QRegularExpression resParse(QString("#((?:D)|(?:V)|(?:R))(\\d+)#"));
    //opParse.setPatternOptions(QRegularExpression::DontCaptureOption); // only capture the whole operation
    QRegularExpressionMatch ResultMatch = resParse.match(formattedString);
    if(ResultMatch.hasMatch())
    {
        DataStruct Result;
        qDebug() << "ResultMatch: " << ResultMatch.captured(1);
        if(ResultMatch.captured(1).compare("D") == 0) // Message data field
        {
            Result.DataType = DataFieldToken;
        }
        else if(ResultMatch.captured(1).compare("V") == 0) // Value
        {
            Result.DataType = ValueToken;
        }
        else if(ResultMatch.captured(1).compare("R") == 0) // Result of preceding operation
        {
            Result.DataType = ResultOfOperationToken;
        }
        qDebug() << "ResultMatch: " << ResultMatch.captured(2);
        Result.DataValue = ResultMatch.captured(2).toInt();

        ValueStore.append(Result);
    }

}

int MsgParser::parseToInt(MsgDataT msgData)
{
    if(ValueStore.size() == 0)
    {
        qDebug() << "ValueStoe has insufficient size: " << ValueStore.size();
        return -1;
    }
    DataStruct curData = ValueStore.last();
    return parseData(curData,msgData);
}

QString MsgParser::getStringPattern() const
{
    return StringPattern;
}

int MsgParser::performOperation(MsgParser::Operation op, MsgDataT msgData)
{
    int operandOne = parseData(op.OperandOne,msgData);
    int operandTwo = parseData(op.OperandTwo,msgData);

    switch(op.opType)
    {
    case add:
        return operandOne + operandTwo;
        break;
    case subtract:
        return operandOne - operandTwo;
        break;
    case multiply:
        return operandOne * operandTwo;
        break;
    case divide:
        return operandOne / operandTwo;
        break;
    case modulo:
        return operandOne % operandTwo;
        break;
    case rightShift:
        return operandOne >> operandTwo;
        break;
    case leftShift:
        return operandOne << operandTwo;
        break;
    case bitAnd:
        return operandOne & operandTwo;
        break;
    case bitOr:
        return operandOne | operandTwo;
        break;
    case bitXor:
        return operandOne ^ operandTwo;
        break;
    default:
        qDebug() << "Error performing Operation: " << "Operation not supported!";
    }
}

int MsgParser::parseData(MsgParser::DataStruct dataToParse, MsgDataT msgData)
{
    int data = 0;
    switch(dataToParse.DataType)
    {
    case DataFieldToken:
         switch(dataToParse.DataValue)
         {
         case 0:
                data = msgData.data0;
             break;
         case 1:
                data = msgData.data1;
             break;
         case 2:
                data = msgData.data2;
             break;
         case 3:
                data = msgData.data3;
             break;
         case 4:
                data = msgData.data4;
             break;
         case 5:
                data = msgData.data5;
             break;
         case 6:
                data = msgData.data6;
             break;
         }
        break;
    case ValueToken:
        data = dataToParse.DataValue;
        break;
    case ResultOfOperationToken:
        data = performOperation(OperationStore.at(dataToParse.DataValue),msgData);
        break;
    case ConversionToken:
        break;
    default:
        qDebug() << "Error parsing DataStruct: " << "DataType not supported!";
    }
    return data;
}
