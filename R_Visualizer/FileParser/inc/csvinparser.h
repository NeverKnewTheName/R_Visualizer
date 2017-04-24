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

    virtual void visit(Msg &visitor);
    virtual void visit(TimestampedMsg &visitor);
    virtual void visit(MsgStreamStore &visitor);
    virtual void visit(MsgStorage &visitor);
    virtual void visit(TimestampedMsgStorage &visitor);
    /* virtual void visit(SendMsgPackageStore &visitor); */
    virtual void visit(MsgIDMappingStore &visitor);
    virtual void visit(MsgIDMapping &visitor);
    virtual void visit(MsgCodeMappingStore &visitor);
    virtual void visit(MsgCodeMapping &visitor);
    virtual void visit(MsgDataMappingStore &visitor);
    virtual void visit(MsgDataMapping &visitor);
    virtual void visit(MsgIDFilterStore &visitor);
    virtual void visit(MsgCodeFilterStore &visitor);
    virtual void visit(MsgTimestampFilter &visitor);

    /* virtual void visit(SysOvrvObject &visitor); */
    /* virtual void visit(SysOvrvTextLabel &visitor); */
    /* virtual void visit(SysOvrvTrigger &visitor); */
    /* virtual void visit(ErrLogModel &visitor); */
    /* virtual void visit(ErrorLogEntry &visitor); */
};

#endif /* CSVINPARSER_H */
