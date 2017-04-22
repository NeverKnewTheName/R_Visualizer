/**
 * @file IMsgDataMappingManager.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief Interface for Message Data Mappings
 */
#ifndef IMSGDATAMAPPINGMANAGER_H
#define IMSGDATAMAPPINGMANAGER_H

#include "IMsgMappingManager.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"

/**
 * @brief The IMsgDataMappingManager interface
 */
class IMsgDataMappingManager : public IMsgMappingManager
{
public:
    virtual ~IMsgDataMappingManager(){}
};

#endif /* IMSGDATAMAPPINGMANAGER_H */
