/**
 * @file PrettyTimestampedMsg.h
 * @author Christian Neuberger
 * @date 2017-03-26
 * 
 * @brief Default implementation of a timestamped IPrettyMsg
 */
#ifndef PRETTYTIMESTAMPEDMSG_H
#define PRETTYTIMESTAMPEDMSG_H

#include <QString>
#include <QColor>
#include <QDateTime>
#include <QFont>
#include <QFontMetrics>
#include <memory>

#include "IPrettyMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "ITimestampedMsg.h"
#include "IMsgDataFormatter.h"

/**
 * @addtogroup PrettyMessageGroup
 * 
 * @{
 */

/**
 * @brief The PrettyTimestampedMsg
 */
template<class ConcreteTimestampedMsg>
class PrettyTimestampedMsg :
    public IPrettyTimestampedMsg
{
public:
    /**
     * @brief Default Constructor for use with QVector..
     */
    PrettyTimestampedMsg() :
        originalMsg(),
        msgIDPlainTextAlias("Default"),
        msgCodePlainTextAlias("Default"),
        msgDataPlainText("Default"),
        msgIDColorRepresentation(Qt::white),
        msgCodeColorRepresentation(Qt::white),
        msgDataColor(Qt::white)
    {
    }

    PrettyTimestampedMsg(const ConcreteTimestampedMsg &originalMsg) :
        originalMsg(originalMsg),
        msgIDPlainTextAlias(static_cast<QString>(originalMsg.getMsgID())),
        msgCodePlainTextAlias(static_cast<QString>(originalMsg.getMsgCode())),
        msgDataPlainText(static_cast<QString>(originalMsg.getMsgData())),
        msgIDColorRepresentation(Qt::white),
        msgCodeColorRepresentation(Qt::white),
        msgDataColor(Qt::white)
    {
    }

    PrettyTimestampedMsg(const PrettyTimestampedMsg &other) :
        originalMsg(other.originalMsg),
        msgIDPlainTextAlias(other.msgIDPlainTextAlias),
        msgCodePlainTextAlias(other.msgCodePlainTextAlias),
        msgDataPlainText(other.msgDataPlainText),
        msgIDColorRepresentation(other.msgIDColorRepresentation),
        msgCodeColorRepresentation(other.msgCodeColorRepresentation),
        msgDataColor(other.msgDataColor)
    {
    }

    virtual ~PrettyTimestampedMsg()
    {
    }

    PrettyTimestampedMsg &operator =(const PrettyTimestampedMsg &other)
    {
        this->originalMsg = other.originalMsg;
        this->msgIDPlainTextAlias = other.msgIDPlainTextAlias;
        this->msgCodePlainTextAlias = other.msgCodePlainTextAlias;
        this->msgDataPlainText = other.msgDataPlainText;
        this->msgIDColorRepresentation = other.msgIDColorRepresentation;
        this->msgCodeColorRepresentation = other.msgCodeColorRepresentation;
        this->msgDataColor = other.msgDataColor;

        return *this;
    }


    QString getMsgIDPlainTextAlias() const
    {
        return msgIDPlainTextAlias;
    }

    void setMsgIDPlainTextAlias(const QString &msgIDAlias)
    {
        this->msgIDPlainTextAlias = msgIDAlias;
    }

    QColor getMsgIDColorRepresentation() const
    {
        return msgIDColorRepresentation;
    }

    void setMsgIDColorRepresentation(const QColor &msgIDColorRepresentation)
    {
        this->msgIDColorRepresentation = msgIDColorRepresentation;
    }

    QString getMsgCodePlainTextAlias() const
    {
        return msgCodePlainTextAlias;
    }

    void setMsgCodePlainTextAlias(const QString &msgCodePlainTextAlias)
    {
        this->msgCodePlainTextAlias = msgCodePlainTextAlias;
    }

    QColor getMsgCodeColorRepresentation() const
    {
        return msgCodeColorRepresentation;
    }

    void setMsgCodeColorRepresentation(const QColor &msgCodeColorRepresentation)
    {
        this->msgCodeColorRepresentation = msgCodeColorRepresentation;
    }

    QString getMsgDataPlainText() const
    {
        return msgDataPlainText;
    }

    void setMsgDataPlainText(const QString &msgDataPlainText)
    {
        this->msgDataPlainText = msgDataPlainText;
    }

    QColor getMsgDataColor() const
    {
        return msgDataColor;
    }

    void setMsgDataColor(const QColor &msgDataColor)
    {
        this->msgDataColor = msgDataColor;
    }

    QSize getMsgIDSizeHint() const
    {
        QFont font;

        const QFontMetrics fontMetrics(font);

        return fontMetrics.size(Qt::TextWordWrap, msgIDPlainTextAlias);
    }

    QSize getMsgCodeSizeHint() const
    {
        QFont font;

        const QFontMetrics fontMetrics(font);

        return fontMetrics.size(Qt::TextWordWrap, msgIDPlainTextAlias);
    }

    QSize getMsgDataSizeHint() const
    {
        QFont font;

        const QFontMetrics fontMetrics(font);

        return fontMetrics.size(Qt::TextWordWrap, msgDataPlainText);
    }

    IMsg *cloneMsg() const
    {
        return new ConcreteTimestampedMsg(originalMsg);
    }

    void setMsgID(const MsgIDType &msgID)
    {
        originalMsg.setMsgID(msgID);
    }
    const MsgIDType getMsgID() const
    {
        return originalMsg.getMsgID();
    }

    void setMsgCode(const MsgCodeType &msgCode)
    {
        originalMsg.setMsgCode(msgCode);
    }
    const MsgCodeType getMsgCode() const
    {
        return originalMsg.getMsgCode();
    }

    void setMsgData(const MsgDataType &msgData)
    {
        originalMsg.setMsgData(msgData);
    }
    const MsgDataType getMsgData() const
    {
        return originalMsg.getMsgData();
    }

    void setTimestamp(const QDateTime &newTimestamp)
    {
        originalMsg.setTimestamp(newTimestamp);
    }

    const QDateTime getTimestamp() const
    {
        return originalMsg.getTimestamp();
    }

    operator QString() const
    {
        return static_cast<QString>(originalMsg);
    }

    void accept(FileParser *visitor)
    {
        originalMsg.accept(visitor);
    }

private:
    ConcreteTimestampedMsg originalMsg;
    QString msgIDPlainTextAlias;
    QString msgCodePlainTextAlias;
    QString msgDataPlainText;
    QColor msgIDColorRepresentation;
    QColor msgCodeColorRepresentation;
    QColor msgDataColor;
};

/**
 * @}
 */
#endif /* PRETTYTIMESTAMPEDMSG_H */
