#ifndef IIDREP_H
#define IIDREP_H

#include "msg.h"
#include "IPlainTextAliasMapping.h"
#include "IColorRepresentationMapping.h"

class IMsgIDRep : public IColorRepresentationMapping, public IPlainTextAliasMapping
{
public:
    virtual ~IMsgIDRep(){}

    virtual MsgIDType getID() const = 0;
    virtual void setID(const MsgIDType id) = 0;
};

#endif /* IIDREP_H */
