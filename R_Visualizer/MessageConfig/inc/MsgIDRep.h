/**
 * \file MsgIDRep.h
 * \author Christian Neuberger
 * \date 2017-02-04
 * 
 * \brief Representation of a MsgID
 */
#ifndef IDREP_H
#define IDREP_H


#include <QString>
#include <QColor>

class FileParser;

#include "Msg.h"
#include "IMsgIDRep.h"
#include "IFileParsable.h"

/**
 * \brief The MsgIDRep class contains all information necessary for displaying a MsgID
 * 
 * The MsgID is displayed according to the name and color mapping
 */
class MsgIDRep : public MsgIDRepCRTPHelper<MsgIDRep>
{
public:
    /**
     * \brief Constructs an empty #MsgIDRep object
     */
    MsgIDRep();
    /**
     * \brief Copies a given #MsgIDRep to this #MsgIDRep
     */
    MsgIDRep(const MsgIDRep& other);
    /**
     * \brief Constructs a plain #MsgIDRep object for the given id
     * 
     * \param[in] id The id to construct the plain #MsgIDRep for
     * 
     * The plain object will have a white background and a default
     * text representation of the id that is the id printed as a hex value.
     */
    MsgIDRep(const MsgIDType id);
    /**
     * \brief Constructs a new #MsgIDRep
     * 
     * \param[in] id The ID the mapping applies to
     * \param[in] name The name the ID is mapped to
     * \param[in] color The color the ID is mapped to
     * 
     */
    MsgIDRep(const MsgIDType id, const QString &name, const QColor &color);

    /**
     * \brief Returns the ID that this #MsgIDRep contain/applies to
     */
    MsgIDType getID() const;

    /**
     * \brief Set the related ID for this #MsgIDRep
     */
    void setID(const MsgIDType id);

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

    /**
     * \brief Copares this #MsgIDRep to another for equality
     * 
     * \note For two #MsgIDRep objects to be considered equal their #id field has to match.
     */
    bool operator==(const MsgIDRep &other) const;

    /**
     * @brief qHash implementation to use #MsgIDRep as a QHash key
     */
    friend uint qHash(const MsgIDRep &key, uint seed)
    {
        return qHash(key.id, seed);
    }

    void accept(FileParser *visitor);


private:
    /**
     * \brief The #MsgIDType this #MsgIDRep object contains the mappings for
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

#endif // IDREP_H
