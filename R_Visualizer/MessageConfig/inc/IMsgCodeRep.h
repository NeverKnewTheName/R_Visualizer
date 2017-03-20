#ifndef IMSGCODEREP_H
#define IMSGCODEREP_H

#include "msg.h"
#include "IPlainTextAliasMapping.h"
#include "IColorRepresentationMapping.h"

class IMsgCodeRep : public IPlainTextAliasMapping, public IColorRepresentationMapping
{
public:
    virtual ~IMsgCodeRep(){}

    MsgCodeType getCode() const = 0;
    void setCode(const MsgCodeType code) = 0;
};

#endif /* IMSGCODEREP_H */
