#include "csvoutparser.h"

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

CsvOutParser::CsvOutParser()
{
}

CsvOutParser::~CsvOutParser()
{
}

void CsvOutParser::visit(IMsg &visitor)
{
}

void CsvOutParser::visit(ITimestampedMsg &visitor)
{
}

void CsvOutParser::visit(IMsgStreamStore &visitor)
{
}

void CsvOutParser::visit(MsgStorage &visitor)
{
}

void CsvOutParser::visit(TimestampedMsgStorage &visitor)
{
}

void CsvOutParser::visit(ISendMsgPackageStore &visitor)
{
}

void CsvOutParser::visit(IMsgIDMappingStore &visitor)
{
}

void CsvOutParser::visit(IMsgIDMapping &visitor)
{
}

void CsvOutParser::visit(IMsgCodeMappingStore &visitor)
{
}

void CsvOutParser::visit(IMsgCodeMapping &visitor)
{
}

void CsvOutParser::visit(IMsgDataMappingStore &visitor)
{
}

void CsvOutParser::visit(IMsgDataMapping &visitor)
{
}

void CsvOutParser::visit(IMsgIDFilterStore &visitor)
{
}

void CsvOutParser::visit(IMsgCodeFilterStore &visitor)
{
}

void CsvOutParser::visit(IMsgTimespanFilter &visitor)
{
}

void CsvOutParser::visit(ISystemOverviewObject &visitor)
{

}

void CsvOutParser::visit(ISysOverviewObjectManager &visitor)
{
}

void CsvOutParser::visit(ISysOverviewObjectColorManager &visitor)
{
}

void CsvOutParser::visit(ISysOverviewObjectResizeManager &visitor)
{
}

void CsvOutParser::visit(SysOverviewTextLabel &visitor)
{
}

void CsvOutParser::visit(ISysOverviewObjectTrigger &visitor)
{
}

void CsvOutParser::visit(ISysOverviewLabelTrigger &visitor)
{
}

void CsvOutParser::visit(ISysOverviewObjectTriggerEvaluator &visitor)
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
