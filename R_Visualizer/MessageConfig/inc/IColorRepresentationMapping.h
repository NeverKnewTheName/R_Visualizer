#ifndef ICOLORREPRESENTATIONMAPPING_H
#define ICOLORREPRESENTATIONMAPPING_H

#include <QColor>

class IColorRepresentationMapping
{
public:
    virtual ~IColorRepresentationMapping(){}

    virtual QColor getColorRepresentation() const = 0;
    virtual void setColorRepresentation(const QColor &colorRepresentation) = 0;
};

#endif /* ICOLORREPRESENTATIONMAPPING_H */
