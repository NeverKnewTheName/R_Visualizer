/**
 * @file csvinparser.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief Visitor parser to parse objects from csv
 */
#ifndef CSVINPARSER_H
#define CSVINPARSER_H

#include "fileparser.h"

/**
 * @brief THe CsvInParser
 */
class CsvInParser : public FileParser
{
public:
    CsvInParser();
    virtual ~CsvInParser();

    virtual void visit(IMsg &visitor);
    virtual void visit(ITimestampedMsg &visitor);
    virtual void visit(IMsgStreamStore &visitor);
    virtual void visit(MsgStorage &visitor);
    virtual void visit(TimestampedMsgStorage &visitor);
    virtual void visit(ISendMsgPackageStore &visitor);
    virtual void visit(IMsgIDMappingStore &visitor);
    virtual void visit(IMsgIDMapping &visitor);
    virtual void visit(IMsgCodeMappingStore &visitor);
    virtual void visit(IMsgCodeMapping &visitor);
    virtual void visit(IMsgDataMappingStore &visitor);
    virtual void visit(IMsgDataMapping &visitor);
    virtual void visit(IMsgIDFilterStore &visitor);
    virtual void visit(IMsgCodeFilterStore &visitor);
    virtual void visit(IMsgTimespanFilter &visitor);

    /* virtual void visit(SysOvrvObject &visitor); */
    /* virtual void visit(SysOvrvTextLabel &visitor); */
    /* virtual void visit(SysOvrvTrigger &visitor); */
    /* virtual void visit(ErrLogModel &visitor); */
    /* virtual void visit(ErrorLogEntry &visitor); */
};

#endif /* CSVINPARSER_H */
