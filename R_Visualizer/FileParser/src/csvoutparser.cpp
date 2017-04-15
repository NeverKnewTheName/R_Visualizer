#include "csvoutparser.h"

#include "Msg.h"
#include "TimestampedMsg.h"
#include "MsgStreamStore.h"
#include "msgstorage.h"
#include "SendMsgPackageStore.h"
#include "MsgIDMappingStore.h"
#include "MsgIDRep.h"
#include "MsgCodeMappingStore.h"
#include "MsgCodeRep.h"
#include "MsgDataMappingStore.h"
#include "MsgDataRep.h"
#include "MsgIDFilterStore.h"
#include "MsgCodeFilterStore.h"
#include "MsgTimestampFilter.h"

#include <QDebug>

CsvOutParser::CsvOutParser()
{
}

CsvOutParser::~CsvOutParser()
{
}

void CsvOutParser::visit(Msg &visitor)
{
}

void CsvOutParser::visit(TimestampedMsg &visitor)
{
}

void CsvOutParser::visit(MsgStreamStore &visitor)
{
}

void CsvOutParser::visit(MsgStorage &visitor)
{
}

void CsvOutParser::visit(TimestampedMsgStorage &visitor)
{
}

void CsvOutParser::visit(SendMsgPackageStore &visitor)
{
}

void CsvOutParser::visit(MsgIDMappingStore &visitor)
{
}

void CsvOutParser::visit(MsgIDRep &visitor)
{
}

void CsvOutParser::visit(MsgCodeMappingStore &visitor)
{
}

void CsvOutParser::visit(MsgCodeRep &visitor)
{
}

void CsvOutParser::visit(MsgDataMappingStore &visitor)
{
}

void CsvOutParser::visit(MsgDataRep &visitor)
{
}

void CsvOutParser::visit(MsgIDFilterStore &visitor)
{
}

void CsvOutParser::visit(MsgCodeFilterStore &visitor)
{
}

void CsvOutParser::visit(MsgTimestampFilter &visitor)
{
}

/* void CsvOutParser::visit(SysOvrvObject &visitor) */
/* { */
/* } */

/* void CsvOutParser::visit(SysOvrvTextLabel &visitor) */
/* { */
/* } */

/* void CsvOutParser::visit(SysOvrvTrigger &visitor) */
/* { */
/* } */

/* void CsvOutParser::visit(ErrLogModel &visitor) */
/* { */
/* } */

/* void CsvOutParser::visit(ErrorLogEntry &visitor) */
/* { */
/* } */
