#include "prettymsg.h"

#include "idrep.h"
#include "msgtyperep.h"
/* #include "msgdatarep.h" */

PrettyMsg::PrettyMsg() :
    Msg(),
    msgIDName(""),
    msgCodeName(""),
    msgIDColor(Qt::black),
    msgCodeColor(Qt::black)
{
}

PrettyMsg::PrettyMsg(
        const Msg &originalMsg,
        const IDRep &idRepresentation,
        const MsgTypeRep &msgTypeRepresentation
        /* const MsgDataRep &msgDataRepresentation */
        ) :
    Msg(originalMsg),
    msgIDName(idRepresentation.getName()),
    msgCodeName(msgTypeRepresentation.getCodeName()),
    /* msgDataString(msgDataRepresentation.getName()), */
    msgIDColor(idRepresentation.getColor()),
    msgCodeColor(msgTypeRepresentation.getColor())
    /* msgDataColor(msgDataRepresentation.getColor()) */
{
}

PrettyMsg::~PrettyMsg()
{
}

QString PrettyMsg::printIDName() const
{
    return msgIDName;
}

QColor PrettyMsg::getIDColor() const
{
    return msgIDColor;
}

QString PrettyMsg::printCodeName() const
{
    return msgCodeName;
}

QColor PrettyMsg::getCodeColor() const
{
    return msgCodeColor;
}

QString PrettyMsg::printDataString() const
{
    return msgDataString;
}

QColor PrettyMsg::getDataColor() const
{
    return msgDataColor;
}

void PrettyMsg::changeIDRep(const IDRep &newIDRep)
{
    msgIDName = newIDRep.getName();
    msgIDColor = newIDRep.getColor();
}

void PrettyMsg::changeMsgTypeRep(const MsgTypeRep &newMsgTypeRep)
{
    msgCodeName = newMsgTypeRep.getCodeName();
    msgCodeColor = newMsgTypeRep.getColor();
}

/* void PrettyMsg::changeDataRep(const MsgDataRep &newMsgDataRep) */
/* { */
/*     msgDataString = newMsgDataRep.getName(); */
/*     msgDataString = newMsgDataREp.getColor(); */
/* } */
