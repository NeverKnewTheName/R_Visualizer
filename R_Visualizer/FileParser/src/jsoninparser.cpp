#include "jsoninparser.h"

#include "messagestream.h"
#include "msgstreammodel.h"
#include "msgstorage.h"
#include "sendmessages.h"
#include "sendmsgmodel.h"
#include "msg.h"
#include "messageconfig.h"
#include "idmodel.h"
#include "idrep.h"
#include "msgtypemodel.h"
#include "msgtyperep.h"
#include "messagefilter.h"
#include "filteridstore.h"
#include "filtercodestore.h"
#include "filtertimestampstore.h"
#include "systemoverview.h"
#include "sysovrvobject.h"
#include "sysovrvtextlabel.h"
#include "sysovrvtrigger.h"
#include "errlogview.h"
#include "errorlogentry.h"


#include <QDebug>

JsonInParser::JsonInParser()
{
}

JsonInParser::~JsonInParser()
{
}

void JsonInParser::visit(MessageStream &visitor)
{
}

void JsonInParser::visit(MsgStreamModel &visitor)
{
}

void JsonInParser::visit(MsgStorage &visitor)
{
}

void JsonInParser::visit(SendMessages &visitor)
{
}

void JsonInParser::visit(SendMsgModel &visitor)
{
}

void JsonInParser::visit(Msg &visitor)
{
}

void JsonInParser::visit(MessageConfig &visitor)
{
}

void JsonInParser::visit(IDModel &visitor)
{
}

void JsonInParser::visit(IDRep &visitor)
{
}

void JsonInParser::visit(MsgTypeModel &visitor)
{
}

void JsonInParser::visit(MsgTypeRep &visitor)
{
}

void JsonInParser::visit(MessageFilter &visitor)
{
}

void JsonInParser::visit(FilterIDStore &visitor)
{
}

void JsonInParser::visit(FilterCodeStore &visitor)
{
}

void JsonInParser::visit(FilterTimestampStore &visitor)
{
}

void JsonInParser::visit(SystemOverview &visitor)
{
}

void JsonInParser::visit(SysOvrvObject &visitor)
{
}

void JsonInParser::visit(SysOvrvTextLabel &visitor)
{
}

void JsonInParser::visit(SysOvrvTrigger &visitor)
{
}

void JsonInParser::visit(ErrorLogView &visitor)
{
}

void JsonInParser::visit(ErrLogModel &visitor)
{
}

void JsonInParser::visit(ErrorLogEntry &visitor)
{
}

