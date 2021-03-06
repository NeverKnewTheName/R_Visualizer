#include "csvinparser.h"


#include "IMsg.h"
#include "ITimestampedMsg.h"
#include "IMsgStreamStore.h"
#include "msgstorage.h"
#include "SendMsgPackageStore.h"
#include "IMsgIDMappingStore.h"
#include "IMsgIDMapping.h"
#include "IMsgCodeMappingStore.h"
#include "IMsgCodeMapping.h"
#include "IMsgDataMappingStore.h"
#include "IMsgDataMapping.h"
#include "IMsgIDFilterStore.h"
#include "IMsgCodeFilterStore.h"
#include "IMsgTimespanFilter.h"

#include "ISystemOverviewObject.h"
#include "ISysOverviewObjectManager.h"
#include "ISysOverviewObjectColorManager.h"
#include "ISysOverviewObjectResizeManager.h"
#include "SysOverviewTextLabel.h"
#include "ISysOverviewObjectTrigger.h"
#include "ISysOverviewLabelTrigger.h"
#include "ISysOverviewObjectTriggerEvaluator.h"

#include <QDebug>

CsvInParser::CsvInParser()
{
}

CsvInParser::~CsvInParser()
{
}

void CsvInParser::visit(IMsg *visitor)
{
}

void CsvInParser::visit(ITimestampedMsg *visitor)
{
}

void CsvInParser::visit(IMsgStreamStore *visitor)
{
}

void CsvInParser::visit(MsgStorage *visitor)
{
}

void CsvInParser::visit(TimestampedMsgStorage *visitor)
{
}

void CsvInParser::visit(ISendMsgPackageStore *visitor)
{
}

void CsvInParser::visit(IMsgIDMappingStore *visitor)
{
}

void CsvInParser::visit(IMsgIDMapping *visitor)
{
}

void CsvInParser::visit(IMsgCodeMappingStore *visitor)
{
}

void CsvInParser::visit(IMsgCodeMapping *visitor)
{
}

void CsvInParser::visit(IMsgDataMappingStore *visitor)
{
}

void CsvInParser::visit(IMsgDataMapping *visitor)
{
}

void CsvInParser::visit(IMsgIDFilterStore *visitor)
{
}

void CsvInParser::visit(IMsgCodeFilterStore *visitor)
{
}

void CsvInParser::visit(IMsgTimespanFilter *visitor)
{
}

void CsvInParser::visit(ISystemOverviewObject *visitor)
{

}

void CsvInParser::visit(ISysOverviewObjectManager *visitor)
{
}

void CsvInParser::visit(ISysOverviewObjectColorManager *visitor)
{
}

void CsvInParser::visit(ISysOverviewObjectResizeManager *visitor)
{
}

void CsvInParser::visit(SysOverviewTextLabel *visitor)
{
}

void CsvInParser::visit(ISysOverviewObjectTrigger *visitor)
{
}

void CsvInParser::visit(ISysOverviewLabelTrigger *visitor)
{
}

void CsvInParser::visit(ISysOverviewObjectTriggerEvaluator *visitor)
{
}

/* void CsvInParser::visit(SysOvrvObject *visitor) */
/* { */
/* } */

/* void CsvInParser::visit(SysOvrvTextLabel *visitor) */
/* { */
/* } */

/* void CsvInParser::visit(SysOvrvTrigger *visitor) */
/* { */
/* } */

/* void CsvInParser::visit(ErrLogModel *visitor) */
/* { */
/* } */

/* void CsvInParser::visit(ErrorLogEntry *visitor) */
/* { */
/* } */



