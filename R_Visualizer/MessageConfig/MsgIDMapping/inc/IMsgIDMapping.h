/**
 * \file IMsgIDMapping.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for a message id mapping
 */
#ifndef IMSGIDMAPPING_H
#define IMSGIDMAPPING_H

#include <memory>

#include "Msg.h"
#include "IPlainTextAliasMapping.h"
#include "IColorRepresentationMapping.h"
#include "IFileParsable.h"

/**
 * \brief The IMsgIDMapping interface
 */
class IMsgIDMapping :
    public IColorRepresentationMapping,
    public IPlainTextAliasMapping,
    public IFileParsable
{
public:
    virtual ~IMsgIDMapping(){}

    virtual IMsgIDMapping *cloneMsgIDMapping() const = 0;

    virtual MsgIDType getID() const = 0;
    virtual void setID(const MsgIDType &id) = 0;

    /* virtual IMsgIDMapping &operator =(const IMsgIDMapping &other) = 0; */
};


/**
 * @brief CRTP copy helper for #IMsgIDMapping
 */
template<class Derived>
class MsgIDMappingCRTPHelper : public IMsgIDMapping
{
public:
    virtual ~MsgIDMappingCRTPHelper(){}

    virtual IMsgIDMapping *cloneMsgIDMapping() const
    {
        return new Derived(static_cast<const Derived&>(*this));
    }
};

#endif /* IMSGIDMAPPING_H */
