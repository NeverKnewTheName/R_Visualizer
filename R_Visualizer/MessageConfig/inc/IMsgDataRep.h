/**
 * \file IMsgDataRep.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for a message data mapping
 */
#ifndef IMSGDATAREP_H
#define IMSGDATAREP_H

#include <memory>

#include <QString>

#include "IMsg.h"
#include "IFileParsable.h"
#include "IMsgDataFormatter.h"

/**
 * \brief The IMsgDataRep interface
 */
class IMsgDataRep : public IFileParsable
{
public:
    virtual ~IMsgDataRep(){}

    virtual std::unique_ptr<IMsgDataRep> cloneMsgDataRep() const = 0;

    virtual MsgIDType getMsgID() const = 0;
    virtual void setMsgID(const MsgIDType id) = 0;

    virtual MsgCodeType getMsgCode() const = 0;
    virtual void setMsgCode(const MsgCodeType code) = 0;

    virtual void setMsgDataFormatter(IMsgDataFormatter *msgDataFormatter) = 0;

    virtual QString parseMsgData(const IMsg &msg) const = 0;
};

/**
 * @brief Typedef of unique_ptr to #IMsgDataRep
 */
typedef std::unique_ptr<IMsgDataRep> IMsgDataRepUniqPtr;

/**
 * @brief CRTP copy helper for #IMsgDataRep
 */
template<class Derived>
class MsgDataRepCRTPHelper : public IMsgDataRep
{
public:
    virtual IMsgDataRepUniqPtr cloneMsgDataRep() const
    {
        return IMsgDataRepUniqPtr(
                new Derived(static_cast<const Derived&>(*this))
                );
    }
};

#endif /* IMSGDATAREP_H */
