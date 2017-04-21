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

    virtual void visit(Msg &visitor);
    virtual void visit(TimestampedMsg &visitor);
    /* virtual void visit(MsgStreamStore &visitor); */
    /* virtual void visit(MsgStorage &visitor); */
    /* virtual void visit(TimestampedMsgStorage &visitor); */
    /* virtual void visit(SendMsgPackageStore &visitor); */
    virtual void visit(MsgIDMappingStore &visitor);
    virtual void visit(MsgIDRep &visitor);
    virtual void visit(MsgCodeMappingStore &visitor);
    virtual void visit(MsgCodeRep &visitor);
    virtual void visit(MsgDataMappingStore &visitor);
    virtual void visit(MsgDataRep &visitor);
    /* virtual void visit(MsgIDFilterStore &visitor); */
    /* virtual void visit(MsgCodeFilterStore &visitor); */
    /* virtual void visit(MsgTimestampFilter &visitor); */

    /* virtual void visit(SysOvrvObject &visitor); */
    /* virtual void visit(SysOvrvTextLabel &visitor); */
    /* virtual void visit(SysOvrvTrigger &visitor); */
    /* virtual void visit(ErrLogModel &visitor); */
    /* virtual void visit(ErrorLogEntry &visitor); */
};

#endif /* CSVOUTPARSER_H */
