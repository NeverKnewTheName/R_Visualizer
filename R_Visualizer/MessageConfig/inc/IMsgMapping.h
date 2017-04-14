/**
 * @file IMsgMapping.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief General interface for message mappings
 */
#ifndef IMSGMAPPING_H
#define IMSGMAPPING_H

#include "IPrettyMsg.h"
#include "IMsg.h"
#include "ITimestampedMsg.h"

#include "IFileParsable.h"

/**
 * @brief The IMsgMapping interface
 */
class IMsgMapping : public IFileParsable
{
public:
    virtual ~IMsgMapping(){}

    /**
     * @brief Prettifies the passed #IPrettyMsg and returns it as a reference
     */
    virtual IPrettyMsg &prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const = 0;
};

#endif /* IMSGMAPPING_H */
