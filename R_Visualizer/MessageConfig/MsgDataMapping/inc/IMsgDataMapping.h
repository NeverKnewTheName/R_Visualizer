/**
 * @file IMsgDataMapping.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief Interface for Message Data Mappings
 */
#ifndef IMSGDATAMAPPING_H
#define IMSGDATAMAPPING_H

#include "IMsgMapping.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"

/**
 * @brief The IMsgDataMapping interface
 */
class IMsgDataMapping : public IMsgMapping
{
public:
    virtual ~IMsgDataMapping(){}
};

#endif /* IMSGDATAMAPPING_H */
