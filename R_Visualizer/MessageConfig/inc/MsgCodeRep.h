/**
 * \file MsgCodeRep.h
 * \author Christian Neuberger
 * \date 2017-02-06
 * 
 * \brief Representation of message codes and data
 */
#ifndef MSGTYPEREP_H
#define MSGTYPEREP_H

#include <QString>
#include <QColor>

class FileParser;

#include "Msg.h"
#include "IMsgCodeRep.h"
#include "IFileParsable.h"

/**
 * \brief The #MsgCodeRep class contains all information necessary for displaying messages codes and data
 */
class MsgCodeRep : public MsgCodeRepCRTPHelper<MsgCodeRep>
{
public:
    /**
     * \brief Constructs an empty #MsgCodeRep
     */
    MsgCodeRep();
    /**
     * \brief Copieas a given #MsgCodeRep to this #MsgCodeRep
     */
    MsgCodeRep(const MsgCodeRep &other);
    /**
     * \brief Constructs a plain #MsgCodeRep object for the given code
     * 
     * \param[in] code The code to construct the plain #MsgCodeRep for
     */
    MsgCodeRep(const MsgCodeType &code);
    /**
     * \brief Constructs a new #MsgCodeRep
     * 
     * \param[in] code The #MsgCodeType this mapping applies to
     * \param[in] name The name the #MsgCodeType is mapped to
     * \param[in] messageFormat The message data parser code the #MsgCodeType applies to
     * \param[in] color The color the #MsgCodeType is mapped to
     *
     */
    MsgCodeRep(const MsgCodeType &code, const QString &name, const QColor &color);

    /**
     * \brief Returns the #MsgCodeType that this #MsgCodeRep contains/applies to
     */
    MsgCodeType getCode() const;

    void setCode(const MsgCodeType &code);

    /**
     * \brief Returns the name this #MsgCodeRep corresponds to
     */
    QString getPlainTextAlias() const;
    /**
     * \brief Sets the name this #MsgCodeRep corresponds to
     */
    void setPlainTextAlias(const QString &plainTextAlias);

    /**
     * \brief Returns the color this #MsgCodeRep corresponds to
     */
    QColor getColorRepresentation() const;
    /**
     * \brief Sets the color this #MsgCodeRep corresponds to
     */
    void setColorRepresentation(const QColor &colorRepresentation);

    IMsgCodeRep &operator =(const IMsgCodeRep &other);

    /**
     * \brief Copares this #MsgCodeRep to another for equality
     */
    bool operator==(const MsgCodeRep &other) const;
    /**
     * \brief Copares this #MsgCodeRep to another #IMsgCodeRep for equality
     * 
     * \note only the contained code is compared!
     */
    bool operator==(const IMsgCodeRep &other) const;

    /**
     * @brief qHash implementation to use #MsgCodeRep as a QHash key
     */
    friend uint qHash(const MsgCodeRep &key, uint seed)
    {
        return qHash(key.code, seed);
    }

    void accept(FileParser *visitor);

private:
    /**
     * \brief The #MsgCodeType this #MsgCodeRep objects contains the mappings for
     */
    MsgCodeType code;
    /**
     * \brief The name that is mapped to the #MsgCodeType
     */
    QString name;
    /* /** */
    /*  * \brief The message data parser code that is used to parse a #Msg's data for the #MsgCodeType */
    /*  *1/ */
    /* QString messageFormat; */
    /**
     * \brief The color that is mapped to the #MsgCodeType
     */
    QColor color;
};

#endif // MSGTYPEREP_H
