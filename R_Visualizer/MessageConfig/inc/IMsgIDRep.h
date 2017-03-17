#ifndef IIDREP_H
#define IIDREP_H

#include <QString>
#include <QColor>

#include "msg.h"
#include "IPlainTextAliasMapping.h"
#include "IColorRepresentationMapping.h"

class IMsgIDRep : public IColorRepresentationMapping, public IPlainTextAliasMapping
{
public:
    IMsgIDRep();
    virtual ~IMsgIDRep();

    MsgIDType getID() const = 0;
    void setID(const MsgIDType id) = 0;
};

#endif /* IIDREP_H */
