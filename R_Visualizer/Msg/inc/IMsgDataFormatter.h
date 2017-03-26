/**
 * @file IMsgDataFormatter.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief Provides an interface for formatters for the message data field
 */
#ifndef IMSGDATAFORMATTER_H
#define IMSGDATAFORMATTER_H

#include <QString>
#include <QColor>

#include "IMsg.h"

/**
 * @brief The IMsgDataFormatter interface
 */
class IMsgDataFormatter
{
public:
    virtual ~IMsgDataFormatter(){}

    virtual std::unique_ptr<IMsgDataFormatter> cloneFormatter() const = 0;
    /**
     * \brief Parses the data field of a message to a QString
     * 
     * \note Since parsing the data could include other fields of a message,
     * the whole message is passed as a parameter.
     */
    virtual QString parseMsgDataToString(const IMsg &msgToParse) const = 0;

    /**
     * \brief Parses the data field of a message to a QColor
     * 
     * \note Since parsing the data could include other fields of a message,
     * the whole message is passed as a parameter.
     */
    virtual QColor parseMsgDataToColor(const IMsg &msgToParse) const = 0;
};

/**
 * @brief Typedef to unique_ptr for #IMsgDataFormatter
 */
using IMsgDataFormatterUniqPtr = std::unique_ptr<IMsgDataFormatter>;

/**
 * @brief CRTP Copy helper for #IMsgDataFormatter
 */
template<class Derived>
class MsgDataFormatterCRTPHelper : public IMsgDataFormatter
{
public:
    /**
     * @brief Clones the current #IMsgDataFormatter derivate whilst conserving
     * its type
     */
    virtual IMsgDataFormatterUniqPtr cloneFormatter() const
    {
        return IMsgDataFormatterUniqPtr(
                new Derived(static_cast<const Derived &>(*this))
                );
    }
};

#endif /* IMSGDATAFORMATTER_H */
