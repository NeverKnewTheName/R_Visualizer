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

#include "IMsgDataFormatter.h"

//ToTHINK create IPrettyMsg from these mixins?
template<class BaseClass>
class IPrettyMsgID : public BaseClass
{
public:
    virtual ~IPrettyMsgID(){}

    virtual QString getMsgIDPlainTextAlias() const = 0;
    virtual void setMsgIDPlainTextAlias(const QString &msgIDAlias) = 0;
    virtual QColor getMsgIDColorRepresentation() const = 0;
    virtual void setMsgIDColorRepresentation(const QColor &msgIDColorRepresentation) = 0;
};

template<class BaseClass>
class IPrettyMsgCode : public BaseClass
{
public:
    virtual ~IPrettyMsgCode(){}

    virtual QString getMsgCodePlainTextAlias() const = 0;
    virtual void setMsgCodePlainTextAlias(const QString &msgCodeAlias) = 0;
    virtual QColor getMsgCodeColorRepresentation() const = 0;
    virtual void setMsgCodeColorRepresentation(const QColor &msgCodeColorRepresentation) = 0;
};

template<class BaseClass>
class IPrettyMsgData : public BaseClass
{
public:
    virtual ~IPrettyMsgData(){}

    virtual QString getParsedMsgDataString() const = 0;
    virtual QColor getParsedMsgDataColor() const = 0;
    virtual void setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter) const = 0;
};
typedef IPrettyMsgID<IPrettyMsgCode<IPrettyMsgData<T>>> IPrettyMsg<T>;

/**
 * @brief The IPrettyMsg interface
 * 
 * \note The interface inherits from all types of message base classes. for
 * instance classes derived from #IMsg or #ITimestampedMsg.
 * 
 * With the help of the template parameter classes that implement this
 * interface can bring in their own functionality regardless of this interface.
 * For instance, a RegularMsg derived from #IMsg has all fields of a message
 * exposed via the corresponding functions, whereas a TimestampedMsg derived
 * from #ITimestampedMsg brings in the timestamp property at no additional cost.
 * 
 * The BaseClass parameter does not even need to be a message since no
 * dependencies on the BaseClass are present.
 */
template<class BaseClass>
class IPrettyMsg : public BaseClass
{
public:
    virtual ~IPrettyMsg(){}

    virtual QString getMsgIDPlainTextAlias() const = 0;
    virtual void setMsgIDPlainTextAlias(const QString &msgIDAlias) = 0;
    virtual QColor getMsgIDColorRepresentation() const = 0;
    virtual void setMsgIDColorRepresentation(const QColor &msgIDColorRepresentation) = 0;

    virtual QString getMsgCodePlainTextAlias() const = 0;
    virtual void setMsgCodePlainTextAlias(const QString &msgCodeAlias) = 0;
    virtual QColor getMsgCodeColorRepresentation() const = 0;
    virtual void setMsgCodeColorRepresentation(const QColor &msgCodeColorRepresentation) = 0;

    virtual QString getParsedMsgDataString() const = 0;
    virtual QColor getParsedMsgDataColor() const = 0;
    virtual void setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter) const = 0;
};

#endif /* IPRETTYMSG_H */
