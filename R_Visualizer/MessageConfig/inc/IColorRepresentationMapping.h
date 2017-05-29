/**
 * \file IColorRepresentationMapping.h
 * \author Christian Neuberger
 * \date 2017-03-20
 * 
 * \brief Provides an interface for classes that have or provide a color
 * representation
 */
#ifndef ICOLORREPRESENTATIONMAPPING_H
#define ICOLORREPRESENTATIONMAPPING_H

#include <QColor>

/**
 * @addtogroup MsgMappingGroup
 * 
 * @{
 */

/**
 * \brief The IColorRepresentationMapping interface
 */
class IColorRepresentationMapping
{
public:
    virtual ~IColorRepresentationMapping(){}

    virtual QColor getColorRepresentation() const = 0;
    virtual void setColorRepresentation(const QColor &colorRepresentation) = 0;
};

/**
 * @}
 */
#endif /* ICOLORREPRESENTATIONMAPPING_H */
