#include "csvinparser.h"

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

CsvInParser::CsvInParser()
{
}

CsvInParser::~CsvInParser()
{
}

void CsvInParser::visit(MessageStream &visitor)
{
}

void CsvInParser::visit(MsgStreamModel &visitor)
{
}

void CsvInParser::visit(MsgStorage &visitor)
{
}

void CsvInParser::visit(SendMessages &visitor)
{
}

void CsvInParser::visit(SendMsgModel &visitor)
{
}

void CsvInParser::visit(Msg &visitor)
{
}

void CsvInParser::visit(MessageConfig &visitor)
{
}

void CsvInParser::visit(IDModel &visitor)
{
}

void CsvInParser::visit(IDRep &visitor)
{
}

void CsvInParser::visit(MsgTypeModel &visitor)
{
}

void CsvInParser::visit(MsgTypeRep &visitor)
{
}

void CsvInParser::visit(MessageFilter &visitor)
{
}

void CsvInParser::visit(FilterIDStore &visitor)
{
}

void CsvInParser::visit(FilterCodeStore &visitor)
{
}

void CsvInParser::visit(FilterTimestampStore &visitor)
{
}

void CsvInParser::visit(SystemOverview &visitor)
{
}

void CsvInParser::visit(SysOvrvObject &visitor)
{
}

void CsvInParser::visit(SysOvrvTextLabel &visitor)
{
}

void CsvInParser::visit(SysOvrvTrigger &visitor)
{
}

void CsvInParser::visit(ErrorLogView &visitor)
{
}

void CsvInParser::visit(ErrLogModel &visitor)
{
}

void CsvInParser::visit(ErrorLogEntry &visitor)
{
}



