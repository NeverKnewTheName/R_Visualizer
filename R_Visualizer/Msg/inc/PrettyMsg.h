/**
 * @file PrettyMsg.h
 * @author Christian Neuberger
 * @date 2017-03-26
 * 
 * @brief A PrettyMsg
 */
#ifndef PRETTYMSG_H
#define PRETTYMSG_H

#include <QString>
#include <QColor>
#include <memory>

#include "IPrettyMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "IMsg.h"
#include "IMsgDataFormatter.h"

class FileParser;

/**
 * @addtogroup PrettyMessageGroup
 * 
 * @{
 */

/**
 * @brief The PrettyMsg
 * 
 * The PrettyMsg class unifies the #IPrettyMsg and the #IMsg interface. This
 * way a PrettyMsg can either be used as an #IPrettyMsg or directly as an #IMsg.
 * The composition approach was chosen to trim down the inheritance hierarchy.
 * 
 * The AbstractMsgCRTPHelper class is used to provide a default implementation of the
 * cloneMsg method.
 */
template<class ConcreteMsg>
class PrettyMsg :
    public IPrettyMsg
{
public:
    /**
     * @brief Default Constructor for use with QVector..
     */
    PrettyMsg() :
        msgDataFormatterUniqPtr(Q_NULLPTR),
        originalMsg(),
        msgIDPlainTextAlias("Default"),
        msgCodePlainTextAlias("Default"),
        msgIDColorRepresentation(Qt::white),
        msgCodeColorRepresentation(Qt::white)
    {
    }

    PrettyMsg(const ConcreteMsg &originalMsg) :
        msgDataFormatterUniqPtr(Q_NULLPTR),
        originalMsg(originalMsg),
        msgIDPlainTextAlias(static_cast<QString>(originalMsg.getMsgID())),
        msgCodePlainTextAlias(static_cast<QString>(originalMsg.getMsgCode())),
        msgIDColorRepresentation(Qt::white),
        msgCodeColorRepresentation(Qt::white)
    {
    }

    PrettyMsg(const PrettyMsg &other) : 
        originalMsg(other.originalMsg),
        msgDataFormatterUniqPtr(other.msgDataFormatterUniqPtr->cloneFormatter()),
        msgIDPlainTextAlias(other.msgIDPlainTextAlias),
        msgCodePlainTextAlias(other.msgCodePlainTextAlias),
        msgIDColorRepresentation(other.msgIDColorRepresentation),
        msgCodeColorRepresentation(other.msgCodeColorRepresentation)
    {
    }

    virtual ~PrettyMsg()
    {
    }

    PrettyMsg &operator =(const PrettyMsg &other)
    {
        this->msgDataFormatterUniqPtr =
            other.msgDataFormatterUniqPtr->cloneFormatter();
        this->originalMsg = other.originalMsg;
        this->msgIDPlainTextAlias = other.msgIDPlainTextAlias;
        this->msgCodePlainTextAlias = other.msgCodePlainTextAlias;
        this->msgIDColorRepresentation = other.msgIDColorRepresentation;
        this->msgCodeColorRepresentation = other.msgCodeColorRepresentation;
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
        return new ConcreteMsg(originalMsg);
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

    operator QString() const
    {
        return static_cast<QString>(originalMsg);
    }

    void accept(FileParser *visitor)
    {
        originalMsg.accept(visitor);
    }

private:
    ConcreteMsg originalMsg;
    std::unique_ptr<IMsgDataFormatter> msgDataFormatterUniqPtr;
    QString msgIDPlainTextAlias;
    QString msgCodePlainTextAlias;
    QColor msgIDColorRepresentation;
    QColor msgCodeColorRepresentation;

    // IMsg interface
public:
    operator QString() const
    {
    }

    // IPrettyMsgData interface
public:
    QSize getMsgDataSizeHint() const
    {
    }

    // IPrettyMsgCode interface
public:
    QSize getMsgCodeSizeHint() const
    {
    }

    // IPrettyMsgID interface
public:
    QSize getMsgIDSizeHint() const
    {
    }

    // IMsg interface
public:
    MessageTypeIdentifier getMsgType() const
    {
        return MessageTypeIdentifier(originalMsg.getMsgID(), originalMsg.getMsgCode());
    }
};

/**
 * @}
 */

#endif /* PRETTYMSG_H */
