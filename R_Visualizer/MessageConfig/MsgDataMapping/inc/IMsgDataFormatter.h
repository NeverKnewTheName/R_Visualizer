/**
 * @file IMsgDataFormatter.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief Provides an interface for formatters for the message data field
 */
#ifndef IMSGDATAFORMATTER_H
#define IMSGDATAFORMATTER_H

#include <QMetaType>
#include <QString>
#include <QColor>

class IMsg;

/**
 * @brief The IMsgDataFormatter interface
 */
class IMsgDataFormatter
{
public:
    virtual ~IMsgDataFormatter(){}

    virtual IMsgDataFormatter *cloneFormatter() const = 0;

    /**
     * @brief Sets the format string that is used by the formatter to format
     * #MsgDataType
     */
    virtual void setFormatString(const QString &formatString) = 0;

    /**
     * @brief Retrieve the currently set format string
     */
    virtual QString getFormatString() const = 0;

    /**
     * @brief Set the default color
     */
    virtual void setDefaultColor(const QColor &defaultColor) = 0;

    /**
     * @brief Retrieve the currently set default color
     */
    virtual QColor getDefaultColor() const = 0;


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
    virtual IMsgDataFormatter *cloneFormatter() const
    {
        return  new Derived(static_cast<const Derived &>(*this));
    }
};

Q_DECLARE_METATYPE(IMsgDataFormatter *)

#endif /* IMSGDATAFORMATTER_H */
