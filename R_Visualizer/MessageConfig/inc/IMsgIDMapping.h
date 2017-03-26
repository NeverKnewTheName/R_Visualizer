/**
 * @file IMsgIDMapping.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief Interface for Message ID Mappings
 */
#ifndef IMSGIDMAPPING_H
#define IMSGIDMAPPING_H

#include "IMsgMapping.h"

#include <QCompleter>

/**
 * @brief The IMsgIDMapping interface
 */
class IMsgIDMapping : public IMsgMapping
{
public:
    virtual ~IMsgIDMapping();

    virtual QCompleter *createIDNameCompleter(
            QObject *parent = Q_NULLPTR
            ) const = 0;
};

#endif /* IMSGIDMAPPING_H */
