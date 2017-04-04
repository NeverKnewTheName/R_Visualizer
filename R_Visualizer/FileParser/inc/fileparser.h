#ifndef FILEPARSER_H
#define FILEPARSER_H

class MsgStreamModel;
class MsgStorage;
class TimestampedMsgStorage;
class SendMsgModel;
class Msg;
class TimestampedMsg;
class MsgIDRep;
class MsgCodeRep;
class MsgDataRep;
class FilterIDStore;
class FilterCodeStore;
class FilterTimestampStore;
class SysOvrvObject;
class SysOvrvTextLabel;
class SysOvrvTrigger;
class ErrLogModel;
class ErrorLogEntry;

class FileParser
{
public:
    FileParser(){}
    virtual ~FileParser(){}

    virtual void visit(MsgStreamModel &visitor) = 0;
    virtual void visit(MsgStorage &visitor) = 0;
    virtual void visit(TimestampedMsgStorage &visitor) = 0;
    virtual void visit(SendMsgModel &visitor) = 0;
    virtual void visit(Msg &visitor) = 0;
    virtual void visit(TimestampedMsg &visitor) = 0;
    virtual void visit(MsgIDRep &visitor) = 0;
    virtual void visit(MsgCodeRep &visitor) = 0;
    virtual void visit(MsgDataRep &visitor) = 0;
    virtual void visit(FilterIDStore &visitor) = 0;
    virtual void visit(FilterCodeStore &visitor) = 0;
    virtual void visit(FilterTimestampStore &visitor) = 0;
    virtual void visit(SysOvrvObject &visitor) = 0;
    virtual void visit(SysOvrvTextLabel &visitor) = 0;
    virtual void visit(SysOvrvTrigger &visitor) = 0;
    virtual void visit(ErrLogModel &visitor) = 0;
    virtual void visit(ErrorLogEntry &visitor) = 0;
};

#endif /* FILEPARSER_H */
