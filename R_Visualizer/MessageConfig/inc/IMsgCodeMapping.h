/**
 * @file IMsgCodeMapping.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief Interface for Message Code Mappings
 */
#ifndef IMSGCODEMAPPING_H
#define IMSGCODEMAPPING_H

#include "IMsgMapping.h"

#include <QCompleter>

/**
 * @brief The IMsgCodeMapping interface
 */
class IMsgCodeMapping : public IMsgMapping
{
public:
    virtual ~IMsgCodeMapping();

    virtual QCompleter *createCodeNameCompleter(
            QObject *parent = Q_NULLPTR
            ) const = 0;
};

#endif /* IMSGCODEMAPPING_H */
