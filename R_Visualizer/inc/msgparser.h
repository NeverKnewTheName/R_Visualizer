//#ifndef MSGPARSER_H
//#define MSGPARSER_H

///*
// *
// * MsgParser
// *
// * MsgParser --- Pattern
// * Token:
// * #CX##\CX#       -- Conversion X with X: 0 1 2 ( DEC HEX BIN ) -- MAY ONLY SURROUND WHOLE OPERATIONS (not inside a nested operation)
// * #OX##\OX#       -- Operation X with X: 0 1 2 3 4 5 6 7 8 9 ( + - * / % >> << & | ^ ) -- can be nested
// * #DX#            -- Data byte nr X with X: 0 1 2 3 4 5 6
// * #VX#            -- Value X with X: integer value
// * #RX#            -- Result of preceding Operation X with X: integer value

// * MsgParser --- Regular Expression
// * Operator
// * #O(\d+)##((?:D)|(?:V)|(?:R))(\d+)##((?:D)|(?:V)|(?:R))(\d+)##\/O\1#  --> CaptureGroups: 1(Operator) 2(OperandOneType) 3(OperandOneValue) 4(OperandTwoType) 5(OperandTwoValue)
// * Converter
// * #C(\d+)##((?:D)|(?:V)|(?:R))(\d+)##\/C\1#
// *
// * MsgParser --- Example
// * Operator
// * #O1##D1##D0##/O1#                    --- Data1 - Data0
// *
// * #O0##O6##D0##V8##/O6##D1##/O0#       --- (Data0 << 8) + Data1    -->  #O0##R0##D1##/O0# with #R0# == Data0 << 8
// * #O0##R0##D1##/O0#                    --- #R0# + Data 1           --> See Above
// *
// * Converter
// * #C0##D0##/C0#                        --- Data0 in DEC
// * #C1##V15##/C1#                       --- 0xF
// * #C2##R0##/C2#                        --- Result of Operation 0 in BIN
// *
// */

//#include <QString>
//#include <QVector>

//#include "msg.h"

//class MsgParser
//{
//public:
//    MsgParser(QString StringPattern);

//    typedef enum
//    {
//        add,
//        subtract,
//        multiply,
//        divide,
//        modulo,
//        rightShift,
//        leftShift,
//        bitAnd,
//        bitOr,
//        bitXor
//    }OperatorToken;

//    typedef enum
//    {
//        DataFieldToken,
//        ValueToken,
//        ResultOfOperationToken,
//        ConversionToken
//    }ParserToken;

//    struct _DataStruct;
//    typedef struct _DataStruct
//    {
//        ParserToken DataType;
//        int         DataValue;
//    }DataStruct;

//    typedef struct _Operation
//    {
//        OperatorToken opType;
//        DataStruct OperandOne;
//        DataStruct OperandTwo;
//    }Operation;

//    int parseToInt(MsgDataT msgData);
//    //    double parseToDouble();

//    QString parseFormattedMessage();

//    QString getStringPattern() const;

//private:
//    int performOperation(Operation op,MsgDataT msgData);
//    int parseData(DataStruct dataToParse,MsgDataT msgData);
//    QString StringPattern;
//    QVector<DataStruct> ValueStore;
//    QVector<Operation> OperationStore;
//};

//#endif // MSGPARSER_H
