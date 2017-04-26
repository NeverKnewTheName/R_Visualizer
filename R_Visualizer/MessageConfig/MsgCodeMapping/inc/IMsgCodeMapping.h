/**
 * \file IMsgCodeMapping
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for a message code mapping
 */
#ifndef IMSGCODEMAPPING_H
#define IMSGCODEMAPPING_H

#include <memory>

#include "Msg.h"
#include "IPlainTextAliasMapping.h"
#include "IColorRepresentationMapping.h"
#include "IFileParsable.h"

/**
 * @addtogroup MsgCodeMappingGroup
 * 
 * @{
 */

/**
 * \brief The IMsgCodeMapping interface
 */
class IMsgCodeMapping :
    public IPlainTextAliasMapping,
    public IColorRepresentationMapping,
    public IFileParsable
{
public:
    virtual ~IMsgCodeMapping(){}

    virtual IMsgCodeMapping *cloneMsgCodeMapping() const = 0;

    virtual MsgCodeType getCode() const = 0;
    virtual void setCode(const MsgCodeType &code) = 0;
};

/**
 * @brief CRTP copy helper for #IMsgCodeMapping
 */
template<class Derived>
class MsgCodeMappingCRTPHelper : public IMsgCodeMapping
{
public:
    virtual ~MsgCodeMappingCRTPHelper(){}

    virtual IMsgCodeMapping *cloneMsgCodeMapping() const
    {
        return new Derived(static_cast<const Derived&>(*this));
    }
};

/**
 * @}
 */

#endif /* IMSGCODEMAPPING_H */
