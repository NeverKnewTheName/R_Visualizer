/**
 * \file idrep.h
 * \author Christian Neuberger
 * \date 2017-02-04
 * 
 * \brief Representation of a MsgID
 */
#ifndef IDREP_H
#define IDREP_H


#include <QJsonObject>
#include <QString>
#include <QColor>
#include <QPixmap>
#include <QStyleOptionViewItem>

class FileParser;

#include "msg.h"
#include "fileparsable.h"

/**
 * \brief The IDRep class contains all information necessary for displaying a MsgID
 * 
 * The MsgID is displayed according to the name and color mapping
 */
class IDRep : public FileParsable
{
public:
    /**
     * \brief Constructs an empty #IDRep object
     */
    IDRep();
    /**
     * \brief Copies a given #IDRep to this #IDRep
     */
    IDRep(const IDRep& other);
    /**
     * \brief Constructs a plain #IDRep object for the given id
     * 
     * \param[in] id The id to construct the plain #IDRep for
     * 
     * The plain object will have a white background and a default
     * text representation of the id that is the id printed as a hex value.
     */
    IDRep(const MsgIDType id);
    /**
     * \brief Constructs a new #IDRep
     * 
     * \param[in] id The ID the mapping applies to
     * \param[in] name The name the ID is mapped to
     * \param[in] color The color the ID is mapped to
     * 
     */
    IDRep(const MsgIDType id, const QString &name, const QColor &color);

    /**
     * \brief Returns the name the ID corresponds to
     */
    QString getName() const;
    /**
     * \brief Sets a name that this ID shall correspond to
     */
    void setName(const QString &value);

    /**
     * \brief Returns the color the ID corresponds to
     */
    QColor getColor() const;
    /**
     * \brief Sets a color that this ID shall correspond to
     */
    void setColor(const QColor &value);

    /**
     * \brief Creates an #IDRep from a QJsonObject
     */
    static IDRep createObjFromJson(const QJsonObject &jsonMsg);
    /**
     * \brief Sets the data of this #IDRep according to the QJsonObject's contents
     */
    void parseIN(const QJsonObject &jsonMsg);
    /**
     * \brief Ouptus the data of this #IDRep to a QJsonObject
     */
    QJsonObject parseOUT() const;

    /**
     * \brief Returns whether this #IDRep is valid
     */
    bool isValid() const;
    /**
     * \brief Copares this #IDRep to another for equality
     * 
     * \note For two #IDRep objects to be considered equal their #id field has to match.
     */
    bool operator==(const IDRep &other) const;

//    IDRep &operator=(const IDRep &other);

    /**
     * \brief Returns the ID that this #IDRep contain/applies to
     */
    MsgIDType getId() const;

    void setId(const MsgIDType id);

    /**
     * \brief Issues a paint of the given ID according to the stored name and color information
     */
    void paintIDRep(QPainter *painter, const QStyleOptionViewItem &option) const;

    void accept(FileParser *visitor);
private:
    /**
     * \brief Stores whether the #IDRep object is valid
     */
    bool isValidObj;
    /**
     * \brief The #MsgIDType this #IDRep object contains the mappings for
     */
    //ToTHINK Keep const?
    MsgIDType id;
    /**
     * \brief The name that is mapped to the id
     */
    QString name;
    /**
     * \brief The color that is mapped to the id
     */
    QColor color;
    /**
     * \brief WHUD?
     */
    QPixmap IDRepPixmap;
};

#endif // IDREP_H
