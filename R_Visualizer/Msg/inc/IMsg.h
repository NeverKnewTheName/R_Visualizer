/**
 * \file IMsg.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief This interface provides the general methods for a Msg class
 */
#ifndef IMSG_H
#define IMSG_H

#include "IFileParsable.h"

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

/**
 * \brief The general interface for all types of messages
 */
class IMsg : public IFileParsable
{
public:
    virtual ~IMsg(){}

    /**
     * @brief IMsg CRTP copy helper
     */
    virtual IMsg *cloneMsg() const = 0;

    /**
     * \brief Set the message's ID
     */
    virtual void setMsgID(const MsgIDType &msgID) = 0;
    /**
     * \brief Retrieve the message's ID
     */
    virtual const MsgIDType getMsgID() const = 0;

    /**
     * \brief Set the message's code
     */
    virtual void setMsgCode(const MsgCodeType &msgCode) = 0;
    /**
     * \brief Retrieve the message's code
     */
    virtual const MsgCodeType getMsgCode() const = 0;

    /**
     * \brief Set the message's data
     */
    virtual void setMsgData(const MsgDataType &msgData) = 0;
    /**
     * \brief Retrieve the message's data
     */
    virtual const MsgDataType getMsgData() const = 0;
};

/**
 * @brief CRTP clone helper to clone #IMsg derivates with only a pointer to the
 * interface
 * 
 * This helper class wraps around #IMsg derivates and implements the cloneMsg
 * method in a way that enables #IMsg derivates to be copied whilst preserving
 * their individual type.
 * 
 * Additionally the mandatory #IFileParsable interface is default implemented
 * here.
 */
template<class Derived>
class AbstractMsgCRTPHelper : public IMsg
{
public:
    virtual IMsg *cloneMsg() const
    {
        return new Derived(static_cast<const Derived&>(*this));
    }
    virtual void accept(FileParser *visitor)
    {
        visitor->visit(static_cast<Derived *>(this));
    }
};

#endif /* IMSG_H */

