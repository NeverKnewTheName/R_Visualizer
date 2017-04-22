/**
 * \file IMsgDataMapping.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for a message data mapping
 */
#ifndef IMSGDATAMAPPING_H
#define IMSGDATAMAPPING_H

#include <memory>

#include <QString>

#include "IMsg.h"
#include "IFileParsable.h"
#include "IMsgDataFormatter.h"

/**
 * \brief The IMsgDataMapping interface
 */
class IMsgDataMapping : public IFileParsable
{
public:
    virtual ~IMsgDataMapping(){}

    virtual IMsgDataMapping *cloneMsgDataMapping() const = 0;

    virtual MsgIDType getMsgID() const = 0;
    virtual void setMsgID(const MsgIDType &id) = 0;

    virtual MsgCodeType getMsgCode() const = 0;
    virtual void setMsgCode(const MsgCodeType &code) = 0;

    virtual IMsgDataFormatter *getMsgDataFormatter() const = 0;
    virtual void setMsgDataFormatter(IMsgDataFormatter *msgDataFormatter) = 0;

    virtual QString parseMsgData(const IMsg &msg) const = 0;
};


/**
 * @brief CRTP copy helper for #IMsgDataMapping
 */
template<class Derived>
class MsgDataMappingCRTPHelper : public IMsgDataMapping
{
public:
    virtual ~MsgDataMappingCRTPHelper(){}
    virtual IMsgDataMapping *cloneMsgDataMapping() const
    {
        return new Derived(static_cast<const Derived&>(*this));
    }
};

#endif /* IMSGDATAMAPPING_H */
