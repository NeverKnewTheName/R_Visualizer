#include "MsgDataFormatter.h"

#include "IMsg.h"

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
    const MsgIDType &msgID = msgToParse.getMsgID();
    const MsgCodeType &msgCode = msgToParse.getMsgCode();
    const MsgDataType &msgData = msgToParse.getMsgData();

    return QString("MsgData parsed");
}

QColor MsgDataFormatter::parseMsgDataToColor(const IMsg &msgToParse) const
{
    return defaultColor;
}
