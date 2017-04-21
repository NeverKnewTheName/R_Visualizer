/**
 * \file IMsgIDRep.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for a message id mapping
 */
#ifndef IIDREP_H
#define IIDREP_H

#include <memory>

#include "Msg.h"
#include "IPlainTextAliasMapping.h"
#include "IColorRepresentationMapping.h"
#include "IFileParsable.h"

/**
 * \brief The IMsgIDRep interface
 */
class IMsgIDRep :
    public IColorRepresentationMapping,
    public IPlainTextAliasMapping,
    public IFileParsable
{
public:
    virtual ~IMsgIDRep(){}

    virtual IMsgIDRep *cloneMsgIDRep() const = 0;

    virtual MsgIDType getID() const = 0;
    virtual void setID(const MsgIDType &id) = 0;

    /* virtual IMsgIDRep &operator =(const IMsgIDRep &other) = 0; */
};


/**
 * @brief CRTP copy helper for #IMsgIDRep
 */
template<class Derived>
class MsgIDRepCRTPHelper : public IMsgIDRep
{
public:
    virtual ~MsgIDRepCRTPHelper(){}

    virtual IMsgIDRep *cloneMsgIDRep() const
    {
        return new Derived(static_cast<const Derived&>(*this));
    }
};

#endif /* IIDREP_H */
