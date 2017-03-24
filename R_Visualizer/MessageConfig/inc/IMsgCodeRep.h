/**
 * \file IMsgCodeRep
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for a message code mapping
 */
#ifndef IMSGCODEREP_H
#define IMSGCODEREP_H

#include "msg.h"
#include "IPlainTextAliasMapping.h"
#include "IColorRepresentationMapping.h"

/**
 * \brief The IMsgCodeRep interface
 */
class IMsgCodeRep : public IPlainTextAliasMapping, public IColorRepresentationMapping
{
public:
    virtual ~IMsgCodeRep(){}

    MsgCodeType getCode() const = 0;
    void setCode(const MsgCodeType code) = 0;
};

#endif /* IMSGCODEREP_H */
