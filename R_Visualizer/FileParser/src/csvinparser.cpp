#include "csvinparser.h"


#include "Msg.h"
#include "TimestampedMsg.h"
/* #include "MsgStreamStore.h" */
/* #include "msgstorage.h" */
/* #include "SendMsgPackageStore.h" */
#include "MsgIDMappingStore.h"
#include "MsgIDRep.h"
#include "MsgCodeMappingStore.h"
#include "MsgCodeRep.h"
#include "MsgDataMappingStore.h"
#include "MsgDataRep.h"
/* #include "MsgIDFilterStore.h" */
/* #include "MsgCodeFilterStore.h" */
/* #include "MsgTimestampFilter.h" */

#include <QDebug>

CsvInParser::CsvInParser()
{
}

CsvInParser::~CsvInParser()
{
}

void CsvInParser::visit(Msg &visitor)
{
}

void CsvInParser::visit(TimestampedMsg &visitor)
{
}

/* void CsvInParser::visit(MsgStreamStore &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(MsgStorage &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(TimestampedMsgStorage &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(SendMsgPackageStore &visitor) */
/* { */
/* } */

void CsvInParser::visit(MsgIDMappingStore &visitor)
{
}

void CsvInParser::visit(MsgIDRep &visitor)
{
}

void CsvInParser::visit(MsgCodeMappingStore &visitor)
{
}

void CsvInParser::visit(MsgCodeRep &visitor)
{
}

void CsvInParser::visit(MsgDataMappingStore &visitor)
{
}

void CsvInParser::visit(MsgDataRep &visitor)
{
}

/* void CsvInParser::visit(MsgIDFilterStore &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(MsgCodeFilterStore &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(MsgTimestampFilter &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(SysOvrvObject &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(SysOvrvTextLabel &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(SysOvrvTrigger &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(ErrLogModel &visitor) */
/* { */
/* } */

/* void CsvInParser::visit(ErrorLogEntry &visitor) */
/* { */
/* } */



