/**
 * @file IPrettyMsg.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief Provides an interface for messages to be pretty printed.
 */
#ifndef IPRETTYMSG_H
#define IPRETTYMSG_H

#include <memory>

#include <QString>
#include <QColor>

#include "IMsgDataFormatter.h"

//ToTHINK create IPrettyMsg from these mixins?
/* template<class BaseClass> */
/* class IPrettyMsgID : public BaseClass */
/* { */
/* public: */
/*     virtual ~IPrettyMsgID(){} */

/*     virtual QString getMsgIDPlainTextAlias() const = 0; */
/*     virtual void setMsgIDPlainTextAlias(const QString &msgIDAlias) = 0; */
/*     virtual QColor getMsgIDColorRepresentation() const = 0; */
/*     virtual void setMsgIDColorRepresentation(const QColor &msgIDColorRepresentation) = 0; */
/* }; */

/* template<class BaseClass> */
/* class IPrettyMsgCode : public BaseClass */
/* { */
/* public: */
/*     virtual ~IPrettyMsgCode(){} */

/*     virtual QString getMsgCodePlainTextAlias() const = 0; */
/*     virtual void setMsgCodePlainTextAlias(const QString &msgCodeAlias) = 0; */
/*     virtual QColor getMsgCodeColorRepresentation() const = 0; */
/*     virtual void setMsgCodeColorRepresentation(const QColor &msgCodeColorRepresentation) = 0; */
/* }; */

/* template<class BaseClass> */
/* class IPrettyMsgData : public BaseClass */
/* { */
/* public: */
/*     virtual ~IPrettyMsgData(){} */

/*     virtual QString getParsedMsgDataString() const = 0; */
/*     virtual QColor getParsedMsgDataColor() const = 0; */
/*     virtual void setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter) const = 0; */
/* }; */
/* typedef IPrettyMsgID<IPrettyMsgCode<IPrettyMsgData<T>>> IPrettyMsg<T>; */

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
    using BaseClass::BaseClass;

    virtual ~IPrettyMsg(){}

    virtual std::unique_ptr<IPrettyMsg<BaseClass>> clonePrettyMsg() const = 0;

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
    virtual void setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter) = 0;
};

/**
 * @brief Typedef for unique_ptr to IPrettyMsg with BaseClass
 */
template<class BaseClass>
using IPrettyMsgUniqPtr = std::unique_ptr<IPrettyMsg<BaseClass>>;

/**
 * @brief CRTP copy helper for derivates of IPrettyMsg
 * 
 * This solves the problem of having to instantiate Derivates from base classes
 * by creating a template for every Derivate. Dynamic Dispatch!
 */
template<class Derivate, class BaseClass>
class PrettyMsgCloneable : public IPrettyMsg<BaseClass>
{
public:
    /**
     * @brief Import Constructors from BaseClas
     */
    using BaseClass::BaseClass;

    /**
     * @brief CRTP Copy helper
     * 
     * Call this function to create a copy of a derivate from a pointer to its
     * BaseClass.
     */
    virtual IPrettyMsgUniqPtr<BaseClass> clonePrettyMsg() const
    {
        return new Derivate(static_cast<const Derivate &>(*this));
    }
};

#endif /* IPRETTYMSG_H */
