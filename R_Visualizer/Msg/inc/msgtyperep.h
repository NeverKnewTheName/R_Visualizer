/**
 * \file msgtyperep.h
 * \author Christian Neuberger
 * \date 2017-02-06
 * 
 * \brief Representation of message codes and data
 */
#ifndef MSGTYPEREP_H
#define MSGTYPEREP_H

#include "msg.h"

#include <QJsonObject>
#include <QString>
#include <QColor>
#include <QPixmap>
#include <QStyleOptionViewItem>


/**
 * \brief The #MsgTypeRep class contains all information necessary for displaying messages codes and data
 */
class MsgTypeRep
{
public:
    /**
     * \brief Constructs an empty #MsgTypeRep
     */
    MsgTypeRep();
    /**
     * \brief Copieas a given #MsgTypeRep to this #MsgTypeRep
     */
    MsgTypeRep(const MsgTypeRep &other);
    /**
     * \brief Constructs a plain #MsgTypeRep object for the given code
     * 
     * \param[in] code The code to construct the plain #MsgTypeRep for
     */
    MsgTypeRep(const MsgCodeType code);
    /**
     * \brief Constructs a new #MsgTypeRep
     * 
     * \param[in] code The #MsgCodeType this mapping applies to
     * \param[in] codeName The name the #MsgCodeType is mapped to
     * \param[in] messageFormat The message data parser code the #MsgCodeType applies to
     * \param[in] color The color the #MsgCodeType is mapped to
     *
     */
    MsgTypeRep(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color);

    /**
     * \brief Returns the #MsgCodeType that this #MsgTypeRep contains/applies to
     */
    MsgCodeType getCode() const;

    /**
     * \brief Returns the name this #MsgTypeRep corresponds to
     */
    QString getCodeName() const;
    /**
     * \brief Sets the name this #MsgTypeRep corresponds to
     */
    void setCodeName(const QString &value);

    /**
     * \brief Returns the message data parser code this #MsgTypeRep corresponds to
     */
    QString getMessageFormat() const;
    /**
     * \brief Sets the message data parser code this #MsgTypeRep corresponds to
     */
    void setMessageFormat(const QString &value);

    /**
     * \brief Returns the color this #MsgTypeRep corresponds to
     */
    QColor getColor() const;
    /**
     * \brief Sets the color this #MsgTypeRep corresponds to
     */
    void setColor(const QColor &value);

    /**
     * \brief Creates an #MsgTypeRep from a QJsonObject
     */
    static MsgTypeRep createObjFromJson(const QJsonObject &jsonMsg);
    /**
     * \brief Sets the data of this #MsgTypeRep according to the QJsonObject's contents
     */
    void parseIN(const QJsonObject &jsonMsg);
    /**
     * \brief Ouptus the data of this #MsgTypeRep to a QJsonObject
     */
    QJsonObject parseOUT() const;

    /**
     * \brief Returns whether this #MsgTypeRep is valid
     */
    bool isValid() const;
    /**
     * \brief Copares this #MsgTypeRep to another for equality
     */
    bool operator==(const MsgTypeRep &other) const;

    /**
     * \brief Returns the string representation of a #Msg according to this #MsgTypeRep
     */
    QString getMsgDataAsString(Msg &msg);
    /**
     * \brief Issues a paint of the given #Msg according to this #MsgTypeRep
     */
    void paintMsgTypeRep(QPainter *painter, const QStyleOptionViewItem &option, Msg &msg) const;

private:
    /**
     * \brief Stores whether the #MsgTypeRep object is valid
     */
    bool isValidObj;
    /**
     * \brief The #MsgCodeType this #MsgTypeRep objects contains the mappings for
     */
    const MsgCodeType code;  //ToDO MsgCodeType...
    /**
     * \brief The name that is mapped to the #MsgCodeType
     */
    QString codeName;
    /**
     * \brief The message data parser code that is used to parse a #Msg's data for the #MsgCodeType
     */
    QString messageFormat;
    /**
     * \brief The color that is mapped to the #MsgCodeType
     */
    QColor color;
    /**
     * \brief Size hint...
     */
    QSize MsgTypeRepSizeHint;
};

#endif // MSGTYPEREP_H
