/**
 * \file MsgCodeMapping.h
 * \author Christian Neuberger
 * \date 2017-02-06
 * 
 * \brief Representation of message codes and data
 */
#ifndef MSGCODEMAPPING_H
#define MSGCODEMAPPING_H

#include <QString>
#include <QColor>

#include "IMsgCodeMapping.h"
#include "MsgCodeType.h"

class FileParser;

/**
 * \brief The #MsgCodeMapping class contains all information necessary for displaying messages codes and data
 */
class MsgCodeMapping : public MsgCodeMappingCRTPHelper<MsgCodeMapping>
{
public:
    /**
     * \brief Constructs an empty #MsgCodeMapping
     */
    MsgCodeMapping();
    /**
     * \brief Copieas a given #MsgCodeMapping to this #MsgCodeMapping
     */
    MsgCodeMapping(const MsgCodeMapping &other);
    /**
     * \brief Constructs a plain #MsgCodeMapping object for the given code
     * 
     * \param[in] code The code to construct the plain #MsgCodeMapping for
     */
    MsgCodeMapping(const MsgCodeType &code);
    /**
     * \brief Constructs a new #MsgCodeMapping
     * 
     * \param[in] code The #MsgCodeType this mapping applies to
     * \param[in] name The name the #MsgCodeType is mapped to
     * \param[in] messageFormat The message data parser code the #MsgCodeType applies to
     * \param[in] color The color the #MsgCodeType is mapped to
     *
     */
    MsgCodeMapping(const MsgCodeType &code, const QString &name, const QColor &color);

    /**
     * \brief Returns the #MsgCodeType that this #MsgCodeMapping contains/applies to
     */
    MsgCodeType getCode() const;

    void setCode(const MsgCodeType &code);

    /**
     * \brief Returns the name this #MsgCodeMapping corresponds to
     */
    QString getPlainTextAlias() const;
    /**
     * \brief Sets the name this #MsgCodeMapping corresponds to
     */
    void setPlainTextAlias(const QString &plainTextAlias);

    /**
     * \brief Returns the color this #MsgCodeMapping corresponds to
     */
    QColor getColorRepresentation() const;
    /**
     * \brief Sets the color this #MsgCodeMapping corresponds to
     */
    void setColorRepresentation(const QColor &colorRepresentation);

    IMsgCodeMapping &operator =(const IMsgCodeMapping &other);

    /**
     * \brief Copares this #MsgCodeMapping to another for equality
     */
    bool operator ==(const MsgCodeMapping &other) const;
    /**
     * \brief Copares this #MsgCodeMapping to another #IMsgCodeMapping for equality
     * 
     * \note only the contained code is compared!
     */
    bool operator ==(const IMsgCodeMapping &other) const;

    /**
     * @brief qHash implementation to use #MsgCodeMapping as a QHash key
     */
    friend uint qHash(const MsgCodeMapping &key, uint seed)
    {
        return qHash(key.code, seed);
    }

    void accept(FileParser *visitor);

private:
    /**
     * \brief The #MsgCodeType this #MsgCodeMapping objects contains the mappings for
     */
    MsgCodeType code;
    /**
     * \brief The name that is mapped to the #MsgCodeType
     */
    QString name;
    /**
     * \brief The color that is mapped to the #MsgCodeType
     */
    QColor color;
};

#endif // MSGCODEMAPPING_H
