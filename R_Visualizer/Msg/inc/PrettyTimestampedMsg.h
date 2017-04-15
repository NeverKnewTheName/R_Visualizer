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
#include <memory>

#include "IPrettyMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "ITimestampedMsg.h"
#include "IMsgDataFormatter.h"

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
        msgDataFormatterUniqPtr(Q_NULLPTR),
        originalMsg(),
        msgIDPlainTextAlias("Default"),
        msgCodePlainTextAlias("Default"),
        msgIDColorRepresentation(Qt::white),
        msgCodeColorRepresentation(Qt::white)
    {
    }

    PrettyTimestampedMsg(const ConcreteTimestampedMsg &originalMsg) :
        msgDataFormatterUniqPtr(Q_NULLPTR),
        originalMsg(originalMsg),
        msgIDPlainTextAlias(static_cast<QString>(originalMsg.getMsgID())),
        msgCodePlainTextAlias(static_cast<QString>(originalMsg.getMsgCode())),
        msgIDColorRepresentation(Qt::white),
        msgCodeColorRepresentation(Qt::white)
    {
    }

    PrettyTimestampedMsg(const PrettyTimestampedMsg &other) :
        originalMsg(other.originalMsg),
        msgDataFormatterUniqPtr(other.msgDataFormatterUniqPtr->cloneFormatter()),
        msgIDPlainTextAlias(other.msgIDPlainTextAlias),
        msgCodePlainTextAlias(other.msgCodePlainTextAlias),
        msgIDColorRepresentation(other.msgIDColorRepresentation),
        msgCodeColorRepresentation(other.msgCodeColorRepresentation)
    {
    }

    virtual ~PrettyTimestampedMsg()
    {
    }

    PrettyTimestampedMsg &operator =(const PrettyTimestampedMsg &other)
    {
        this->msgDataFormatterUniqPtr = std::unique_ptr<IMsgDataFormatter>(
            other.msgDataFormatterUniqPtr->cloneFormatter()
                    );
        this->originalMsg = other.originalMsg;
        this->msgIDPlainTextAlias = other.msgIDPlainTextAlias;
        this->msgCodePlainTextAlias = other.msgCodePlainTextAlias;
        this->msgIDColorRepresentation = other.msgIDColorRepresentation;
        this->msgCodeColorRepresentation = other.msgCodeColorRepresentation;

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

    /**
     * //ToTHINK
     * MAYBE DO NOT PROCESS MSG DATA FOR EACH FUNCTION CALL HERE...
     */
    QString getParsedMsgDataString() const
    {
        //Check if the MsgDataFormatter is a nullptr
        if(msgDataFormatterUniqPtr.get() == nullptr)
        {
            QString msgDataAsDefaultString;
            MsgDataType msgData = getMsgData();
            for(const MsgDataByteType &dataByte : msgData)
            {
                QString msgDataByteAsString("0x%1 ");
                msgDataByteAsString.arg(static_cast<QString>(dataByte));
                msgDataAsDefaultString.prepend(msgDataByteAsString);
            }
            return msgDataAsDefaultString;
        }

        return msgDataFormatterUniqPtr->parseMsgDataToString(*this);
    }

    QColor getParsedMsgDataColor() const
    {
        //Check if the MsgDataFormatter is a nullptr
        if(msgDataFormatterUniqPtr.get() == nullptr)
        {
            return QColor(Qt::white);
        }

        return msgDataFormatterUniqPtr->parseMsgDataToColor(*this);
    }

    void setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter)
    {
        this->msgDataFormatterUniqPtr =
           std::unique_ptr<IMsgDataFormatter>(
                   msgDataFormatter.cloneFormatter()
                   );
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

    void accept(FileParser *visitor)
    {
        originalMsg.accept(visitor);
    }

private:
    ConcreteTimestampedMsg originalMsg;
    std::unique_ptr<IMsgDataFormatter> msgDataFormatterUniqPtr;
    QString msgIDPlainTextAlias;
    QString msgCodePlainTextAlias;
    QColor msgIDColorRepresentation;
    QColor msgCodeColorRepresentation;
};

#endif /* PRETTYTIMESTAMPEDMSG_H */
