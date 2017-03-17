#ifndef ICOLORREPRESENTATIONMAPPING_H
#define ICOLORREPRESENTATIONMAPPING_H

#include <QColor>

class IColorRepresentationMapping
{
public:
    IColorRepresentationMapping();
    virtual ~IColorRepresentationMapping();

    QColor getColorRepresentation() const = 0;
    void setColorRepresentation(const QColor &colorRepresentation) = 0;

};

#endif /* ICOLORREPRESENTATIONMAPPING_H */
