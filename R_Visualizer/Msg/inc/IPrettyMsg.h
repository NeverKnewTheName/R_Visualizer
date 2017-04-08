/**
 * @file IPrettyMsg.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief Provides an interface for messages to be pretty printed.
 */
#ifndef IPRETTYMSG_H
#define IPRETTYMSG_H

#include <QString>
#include <QColor>

class IMsgDataFormatter;

/**
 * @brief The IPrettyMsgID interface
 */
class IPrettyMsgID
{
public:
    virtual ~IPrettyMsgID(){}

    virtual QString getMsgIDPlainTextAlias() const = 0;
    virtual void setMsgIDPlainTextAlias(const QString &msgIDAlias) = 0;
    virtual QColor getMsgIDColorRepresentation() const = 0;
    virtual void setMsgIDColorRepresentation(
            const QColor &msgIDColorRepresentation
            ) = 0;
};

/**
 * @brief The IPrettyMsgCode interface
 */
class IPrettyMsgCode
{
public:
    virtual ~IPrettyMsgCode(){}

    virtual QString getMsgCodePlainTextAlias() const = 0;
    virtual void setMsgCodePlainTextAlias(const QString &msgCodeAlias) = 0;
    virtual QColor getMsgCodeColorRepresentation() const = 0;
    virtual void setMsgCodeColorRepresentation(
            const QColor &msgCodeColorRepresentation
            ) = 0;
};

/**
 * @brief The IPrettyMsgData interface
 */
class IPrettyMsgData
{
public:
    virtual ~IPrettyMsgData(){}

    virtual QString getParsedMsgDataString() const = 0;
    virtual QColor getParsedMsgDataColor() const = 0;
    virtual void setMsgDataFormatter(
            const IMsgDataFormatter &msgDataFormatter
            ) = 0;
};

/**
 * @brief The IPrettyMsg interface
 */
class IPrettyMsg :
    public IPrettyMsgID,
    public IPrettyMsgCode,
    public IPrettyMsgData
{
public:
    virtual ~IPrettyMsg(){}
};

template<class Derived>
class AbstractCloneablePrettyMsg : public IPrettyMsg
{
public:
    virtual ~AbstractCloneablePrettyMsg(){}

    virtual IPrettyMsg *clonePrettyMsg() const
    {
        return new Derived(static_cast<const Derived &>(*this));
    }
}

#endif /* IPRETTYMSG_H */
