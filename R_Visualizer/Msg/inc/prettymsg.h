/**
 * \file prettymsg.h
 * \author Christian Neuberger
 * \date 2017-02-09
 * 
 * \brief Wrapper for a #Msg object to be pretty printed according
 * to several Rep objects.
 * 
 */
#ifndef PRETTYMSG_H
#define PRETTYMSG_H

#include <QString>
#include <QColor>
#include <QSize>

class IDRep;
class MsgTypeRep;
/* class MsgDataRep; */

#include "msg.h"

class PrettyMsg : public Msg
{
public:
    PrettyMsg();
    PrettyMsg(const Msg &originalMsg);
    PrettyMsg(
        const Msg &originalMsg,
        const IDRep &idRepresentation,
        const MsgTypeRep &msgTypeRepresentation
        /* const MsgDataRep &msgDataRepresentation */
    );
    virtual ~PrettyMsg();

    //ToTHINK ...maybe return references instead??
    QString printIDName() const;
    QColor getIDColor() const;
    QString printCodeName() const;
    QColor getCodeColor() const;
    QString printDataString() const;
    QColor getDataColor() const;

    void changeIDRep(const IDRep &newIDRep);
    void changeMsgTypeRep(const MsgTypeRep &newMsgTypeRep);
    /* void changeDataRep(const MsgDataRep &newMsgDataRep) */

private:
    QString msgIDName;
    QString msgCodeName;
    QString msgDataString;
    QColor msgIDColor;
    QColor msgCodeColor;
    QColor msgDataColor;
    QSize msgIDSize;
    QSize msgCodeSize;
};

#endif /* PRETTYMSG_H */
