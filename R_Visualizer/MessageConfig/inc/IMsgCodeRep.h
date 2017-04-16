/**
 * \file IMsgCodeRep
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for a message code mapping
 */
#ifndef IMSGCODEREP_H
#define IMSGCODEREP_H

#include <memory>

#include "Msg.h"
#include "IPlainTextAliasMapping.h"
#include "IColorRepresentationMapping.h"
#include "IFileParsable.h"

/**
 * \brief The IMsgCodeRep interface
 */
class IMsgCodeRep :
    public IPlainTextAliasMapping,
    public IColorRepresentationMapping,
    public IFileParsable
{
public:
    virtual ~IMsgCodeRep(){}

    virtual IMsgCodeRep *cloneMsgCodeRep() const = 0;

    virtual MsgCodeType getCode() const = 0;
    virtual void setCode(const MsgCodeType &code) = 0;
};

/**
 * @brief CRTP copy helper for #IMsgCodeRep
 */
template<class Derived>
class MsgCodeRepCRTPHelper : public IMsgCodeRep
{
public:
    virtual ~MsgCodeRepCRTPHelper(){}

    virtual IMsgCodeRep *cloneMsgCodeRep() const
    {
        return new Derived(static_cast<const Derived&>(*this));
    }
};

#endif /* IMSGCODEREP_H */
