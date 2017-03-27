#include "csvoutparser.h"

#include "messagestream.h"
#include "msgstreammodel.h"
#include "msgstorage.h"
#include "sendmessages.h"
#include "sendmsgmodel.h"
#include "Msg.h"
#include "MessageConfig.h"
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

CsvOutParser::CsvOutParser()
{
}

CsvOutParser::~CsvOutParser()
{
}

void CsvOutParser::visit(MessageStream &visitor)
{
}

void CsvOutParser::visit(MsgStreamModel &visitor)
{
}

void CsvOutParser::visit(MsgStorage &visitor)
{
}

void CsvOutParser::visit(SendMessages &visitor)
{
}

void CsvOutParser::visit(SendMsgModel &visitor)
{
}

void CsvOutParser::visit(Msg &visitor)
{
}

void CsvOutParser::visit(MessageConfig &visitor)
{
}

void CsvOutParser::visit(IDModel &visitor)
{
}

void CsvOutParser::visit(IDRep &visitor)
{
}

void CsvOutParser::visit(MsgTypeModel &visitor)
{
}

void CsvOutParser::visit(MsgTypeRep &visitor)
{
}

void CsvOutParser::visit(MessageFilter &visitor)
{
}

void CsvOutParser::visit(FilterIDStore &visitor)
{
}

void CsvOutParser::visit(FilterCodeStore &visitor)
{
}

void CsvOutParser::visit(FilterTimestampStore &visitor)
{
}

void CsvOutParser::visit(SystemOverview &visitor)
{
}

void CsvOutParser::visit(SysOvrvObject &visitor)
{
}

void CsvOutParser::visit(SysOvrvTextLabel &visitor)
{
}

void CsvOutParser::visit(SysOvrvTrigger &visitor)
{
}

void CsvOutParser::visit(ErrorLogView &visitor)
{
}

void CsvOutParser::visit(ErrLogModel &visitor)
{
}

void CsvOutParser::visit(ErrorLogEntry &visitor)
{
}
