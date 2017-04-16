/**
 * @file IMsgDataMappingStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The interface for MsgData Mapping stores
 */
#ifndef IMSGDATAMAPPINGSTORE_H
#define IMSGDATAMAPPINGSTORE_H

#include "IFileParsable.h"

class IMsgDataMappingStore : public IFileParsable
{
public:
    virtual ~IMsgDataMappingStore(){}

    /* virtual */ 
};

#endif /* IMSGDATAMAPPINGSTORE_H */
