#ifndef PRETTYMSG_H
#define PRETTYMSG_H

#include <QString>
#include <QColor>
#include <QSize>

#include "msg.h"

class PrettyMsg : public Msg
{
public:
    PrettyMsg(const Msg &originalMsg, const IDRep &representation);
    virtual ~PrettyMsg();
private:
    QString msgName;
    QColor msgColor;
    QSize msgSize;
};

#endif /* PRETTYMSG_H */
