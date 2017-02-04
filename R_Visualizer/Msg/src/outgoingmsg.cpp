#include "msg.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>

OutgoingMsg::OutgoingMsg( const MsgIDType &id, const MsgCodeType &code, const DataByteVect &dataBytes ) :
    Msg(id, code, dataBytes)
{
    
}
