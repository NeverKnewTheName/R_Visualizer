/**
 * \file MsgIDMapping.h
 * \author Christian Neuberger
 * \date 2017-02-04
 * 
 * \brief Representation of a MsgID
 */
#ifndef MSGIDMAPPING_H
#define MSGIDMAPPING_H


#include <QString>
#include <QColor>

#include "IMsgIDMapping.h"
#include "MsgIDType.h"

class FileParser;

/**
 * \brief The MsgIDMapping class contains all information necessary for displaying a
 * MsgID
 * 
 * The MsgID is displayed according to the name and color mapping
 */
class MsgIDMapping : public MsgIDMappingCRTPHelper<MsgIDMapping>
{
public:
    /**
     * \brief Constructs an empty #MsgIDMapping object
     */
    MsgIDMapping();
    /**
     * \brief Copies a given #MsgIDMapping to this #MsgIDMapping
     */
    MsgIDMapping(const MsgIDMapping& other);
    /**
     * \brief Constructs a plain #MsgIDMapping object for the given id
     * 
     * \param[in] id The id to construct the plain #MsgIDMapping for
     * 
     * The plain object will have a white background and a default
     * text representation of the id that is the id printed as a hex value.
     */
    MsgIDMapping(const MsgIDType &id);
    /**
     * \brief Constructs a new #MsgIDMapping
     * 
     * \param[in] id The ID the mapping applies to
     * \param[in] name The name the ID is mapped to
     * \param[in] color The color the ID is mapped to
     * 
     */
    MsgIDMapping(const MsgIDType &id, const QString &name, const QColor &color);

    /**
     * \brief Returns the ID that this #MsgIDMapping contain/applies to
     */
    MsgIDType getID() const;

    /**
     * \brief Set the related ID for this #MsgIDMapping
     */
    void setID(const MsgIDType &id);

    /**
     * \brief Returns the name the ID corresponds to
     */
    /* QString getName() const; */
    QString getPlainTextAlias() const;

    /**
     * \brief Sets a name that this ID shall correspond to
     */
    /* void setName(const QString &value); */
    void setPlainTextAlias(const QString &plainTextAlias);

    /**
     * \brief Returns the color the ID corresponds to
     */
    /* QColor getColor() const; */
    QColor getColorRepresentation() const;

    /**
     * \brief Sets a color that this ID shall correspond to
     */
    /* void setColor(const QColor &value); */
    void setColorRepresentation(const QColor &colorRepresentation);

    IMsgIDMapping &operator =(const IMsgIDMapping &other);

    /**
     * \brief Copares this #MsgIDMapping to another for equality
     * 
     * \note For two #MsgIDMapping objects to be considered equal their #id field has to match.
     */
    bool operator ==(const MsgIDMapping &other) const;
    bool operator ==(const IMsgIDMapping &other) const;

    /**
     * @brief qHash implementation to use #MsgIDMapping as a QHash key
     */
    friend uint qHash(const MsgIDMapping &key, uint seed)
    {
        return qHash(key.id, seed);
    }

    void accept(FileParser *visitor);


private:
    /**
     * \brief The #MsgIDType this #MsgIDMapping object contains the mappings for
     */
    MsgIDType id;
    /**
     * \brief The name that is mapped to the id
     */
    QString name;
    /**
     * \brief The color that is mapped to the id
     */
    QColor color;
};

#endif // MSGIDMAPPING_H
