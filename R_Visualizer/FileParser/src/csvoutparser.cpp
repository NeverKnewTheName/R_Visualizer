#include "csvoutparser.h"

#include "msgstreammodel.h"
#include "msgstorage.h"
#include "sendmsgmodel.h"
#include "Msg.h"
#include "MsgIDRep.h"
#include "MsgCodeRep.h"
#include "MsgDataRep.h"
#include "filteridstore.h"
#include "filtercodestore.h"
#include "filtertimestampstore.h"
#include "sysovrvobject.h"
#include "sysovrvtextlabel.h"
#include "sysovrvtrigger.h"
#include "errorlogentry.h"


#include <QDebug>

CsvOutParser::CsvOutParser()
{
}

CsvOutParser::~CsvOutParser()
{
}

/* void CsvOutParser::visit(MessageStream &visitor) */
/* { */
/* } */

void CsvOutParser::visit(MsgStreamModel &visitor)
{
}

void CsvOutParser::visit(MsgStorage &visitor)
{
}

void CsvOutParser::visit(TimestampedMsgStorage &visitor)
{
}

/* void CsvOutParser::visit(SendMessages &visitor) */
/* { */
/* } */

void CsvOutParser::visit(SendMsgModel &visitor)
{
}

void CsvOutParser::visit(Msg &visitor)
{
}

void CsvOutParser::visit(TimestampedMsg &visitor)
{
}

/* void CsvOutParser::visit(MessageConfig &visitor) */
/* { */
/* } */

/* void CsvOutParser::visit(IDModel &visitor) */
/* { */
/* } */

void CsvOutParser::visit(MsgIDRep &visitor)
{
}

/* void CsvOutParser::visit(MsgTypeModel &visitor) */
/* { */
/* } */

void CsvOutParser::visit(MsgCodeRep &visitor)
{
}

void CsvOutParser::visit(MsgDataRep &visitor)
{
}

/* void CsvOutParser::visit(MessageFilter &visitor) */
/* { */
/* } */

void CsvOutParser::visit(FilterIDStore &visitor)
{
}

void CsvOutParser::visit(FilterCodeStore &visitor)
{
}

void CsvOutParser::visit(FilterTimestampStore &visitor)
{
}

/* void CsvOutParser::visit(SystemOverview &visitor) */
/* { */
/* } */

void CsvOutParser::visit(SysOvrvObject &visitor)
{
}

void CsvOutParser::visit(SysOvrvTextLabel &visitor)
{
}

void CsvOutParser::visit(SysOvrvTrigger &visitor)
{
}

/* void CsvOutParser::visit(ErrorLogView &visitor) */
/* { */
/* } */

void CsvOutParser::visit(ErrLogModel &visitor)
{
}

void CsvOutParser::visit(ErrorLogEntry &visitor)
{
}
