/**
 * @file csvoutparser.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief Visitor parser to parse objects to csv
 */
#ifndef CSVOUTPARSER_H
#define CSVOUTPARSER_H

#include "fileparser.h"

/**
 * @brief The CsvOutParser
 */
class CsvOutParser : public FileParser
{
public:
    CsvOutParser();
    virtual ~CsvOutParser();

    virtual void visit(IMsg *visitor);
    virtual void visit(ITimestampedMsg *visitor);
    virtual void visit(IMsgStreamStore *visitor);
    virtual void visit(MsgStorage *visitor);
    virtual void visit(TimestampedMsgStorage *visitor);
    virtual void visit(ISendMsgPackageStore *visitor);
    virtual void visit(IMsgIDMappingStore *visitor);
    virtual void visit(IMsgIDMapping *visitor);
    virtual void visit(IMsgCodeMappingStore *visitor);
    virtual void visit(IMsgCodeMapping *visitor);
    virtual void visit(IMsgDataMappingStore *visitor);
    virtual void visit(IMsgDataMapping *visitor);
    virtual void visit(IMsgIDFilterStore *visitor);
    virtual void visit(IMsgCodeFilterStore *visitor);
    virtual void visit(IMsgTimespanFilter *visitor);

    virtual void visit(ISystemOverviewObject *visitor);

    /* virtual void visit(SysOvrvObject *visitor); */
    /* virtual void visit(SysOvrvTextLabel *visitor); */
    /* virtual void visit(SysOvrvTrigger *visitor); */
    /* virtual void visit(ErrLogModel *visitor); */
    /* virtual void visit(ErrorLogEntry *visitor); */

    // FileParser interface
public:
    virtual void visit(ISysOverviewObjectManager *visitor);
    virtual void visit(ISysOverviewObjectColorManager *visitor);
    virtual void visit(ISysOverviewObjectResizeManager *visitor);
    virtual void visit(SysOverviewTextLabel *visitor);
    virtual void visit(ISysOverviewObjectTrigger *visitor);
    virtual void visit(ISysOverviewLabelTrigger *visitor);
    virtual void visit(ISysOverviewObjectTriggerEvaluator *visitor);
};

#endif /* CSVOUTPARSER_H */
