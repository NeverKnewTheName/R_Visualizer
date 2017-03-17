#ifndef COLORREPRESENTATIONMAPPING_H
#define COLORREPRESENTATIONMAPPING_H

#include <QColor>

class ColorRepresentationMapping
{
public:
    ColorRepresentationMapping();
    virtual ~ColorRepresentationMapping();

    QColor getColorRepresentation() const = 0;
    void setColorRepresentation(const QColor &colorRepresentation) = 0;

};

#endif /* COLORREPRESENTATIONMAPPING_H */
