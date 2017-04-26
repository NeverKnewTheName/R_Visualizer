/**
 * @file ITimestamp.h
 * @author Christian Neuberger
 * @date 2017-04-24
 * 
 * @brief Interface for timestamps
 */
#ifndef ITIMESTAMP_H
#define ITIMESTAMP_H

#include <QDateTime>

/**
 * @defgroup TimestampGroup Timestamp
 * @ingroup MessageGroup
 * 
 * @{
 */

/**
 * @brief The ITimestamp interface provides methods to organize a timestamp
 * 
 * Implement this interface to be able to add a timestamp property to classes
 */
class ITimestamp
{
public:
    virtual ~ITimestamp(){}

    /**
     * @brief Set the timestam
     * 
     * @param[in] newTimestamp The timestamp to set
     */
    virtual void setTimestamp(const QDateTime &newTimestamp) = 0;
    /**
     * @brief Retrieve the currently set timestamp
     * 
     * @returns The currently set timestamp as a QkDateTime
     */
    virtual const QDateTime getTimestamp() const = 0;
};

/**
 * @}
 */
#endif /* ITIMESTAMP_H */
