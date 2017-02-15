#ifndef CSVOUTPARSER_H
#define CSVOUTPARSER_H

#include "fileparser.h"

class CsvOutParser : public FileParser
{
public:
    CsvOutParser();
    virtual ~CsvOutParser();

    void visit(MessageStream &visitor);
    void visit(MsgStreamModel &visitor);
    void visit(MsgStorage &visitor);
    void visit(SendMessages &visitor);
    void visit(SendMsgModel &visitor);
    void visit(Msg &visitor);
    void visit(MessageConfig &visitor);
    void visit(IDModel &visitor);
    void visit(IDRep &visitor);
    void visit(MsgTypeModel &visitor);
    void visit(MsgTypeRep &visitor);
    void visit(MessageFilter &visitor);
    void visit(FilterIDStore &visitor);
    void visit(FilterCodeStore &visitor);
    void visit(FilterTimestampStore &visitor);
    void visit(SystemOverview &visitor);
    void visit(SysOvrvObject &visitor);
    void visit(SysOvrvTextLabel &visitor);
    void visit(SysOvrvTrigger &visitor);
    void visit(ErrorLogView &visitor);
    void visit(ErrLogModel &visitor);
    void visit(ErrorLogEntry &visitor);
};

#endif /* CSVOUTPARSER_H */
