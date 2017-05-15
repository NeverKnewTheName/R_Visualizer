/**
 * @file MsgDataFormatter.h
 * @author Christian Neuberger
 * @date 2017-04-23
 * 
 * @brief The default implementation of the #IMsgDataFormatter
 */
#ifndef MSGDATAFORMATTER_H
#define MSGDATAFORMATTER_H

#include "IMsgDataFormatter.h"


#include <QString>
#include <QColor>

/**
 * @brief The MsgDataFormatter
 */
class MsgDataFormatter :
    public MsgDataFormatterCRTPHelper<MsgDataFormatter>
{
public:
    MsgDataFormatter(
            const QString &formatString = QString(),
            const QColor &defaultColor = QColor(Qt::lightGray)
            );
    virtual ~MsgDataFormatter();

    /**
     * @brief Set the format string
     */
    virtual void setFormatString(const QString &formatString);

    /**
     * @brief Retrieve the currently set format string
     */
    virtual QString getFormatString() const;

    /**
     * @brief Set the default color
     */
    virtual void setDefaultColor(const QColor &defaultColor);

    /**
     * @brief Retrieve the currently set default color
     */
    virtual QColor getDefaultColor() const;

    /**
     * \brief Parses the data field of a message to a QString
     * 
     * \note Since parsing the data could include other fields of a message,
     * the whole message is passed as a parameter.
     */
    virtual QString parseMsgDataToString(const IMsg &msgToParse) const;

    /**
     * \brief Parses the data field of a message to a QColor
     * 
     * \note Since parsing the data could include other fields of a message,
     * the whole message is passed as a parameter.
     */
    virtual QColor parseMsgDataToColor(const IMsg &msgToParse) const;
private:
    QString formatString;
    QColor defaultColor;
};


#endif /* MSGDATAFORMATTER_H */
