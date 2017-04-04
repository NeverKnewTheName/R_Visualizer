#include "csvinparser.h"


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

CsvInParser::CsvInParser()
{
}

CsvInParser::~CsvInParser()
{
}

/* void CsvInParser::visit(MessageStream &visitor) */
/* { */
/* } */

void CsvInParser::visit(MsgStreamModel &visitor)
{
}

void CsvInParser::visit(MsgStorage &visitor)
{
}

void CsvInParser::visit(TimestampedMsgStorage &visitor)
{
}

/* void CsvInParser::visit(SendMessages &visitor) */
/* { */
/* } */

void CsvInParser::visit(SendMsgModel &visitor)
{
}

void CsvInParser::visit(Msg &visitor)
{
}

void CsvInParser::visit(TimestampedMsg &visitor)
{
}

/* void CsvInParser::visit(MessageConfig &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(IDModel &visitor) */
/* { */
/* } */

void CsvInParser::visit(MsgIDRep &visitor)
{
}

/* void CsvInParser::visit(MsgTypeModel &visitor) */
/* { */
/* } */

void CsvInParser::visit(MsgCodeRep &visitor)
{
}

void CsvInParser::visit(MsgDataRep &visitor)
{
}

/* void CsvInParser::visit(MessageFilter &visitor) */
/* { */
/* } */

void CsvInParser::visit(FilterIDStore &visitor)
{
}

void CsvInParser::visit(FilterCodeStore &visitor)
{
}

void CsvInParser::visit(FilterTimestampStore &visitor)
{
}

/* void CsvInParser::visit(SystemOverview &visitor) */
/* { */
/* } */

void CsvInParser::visit(SysOvrvObject &visitor)
{
}

void CsvInParser::visit(SysOvrvTextLabel &visitor)
{
}

void CsvInParser::visit(SysOvrvTrigger &visitor)
{
}

/* void CsvInParser::visit(ErrorLogView &visitor) */
/* { */
/* } */

void CsvInParser::visit(ErrLogModel &visitor)
{
}

void CsvInParser::visit(ErrorLogEntry &visitor)
{
}



