#ifndef FILEPARSER_H
#define FILEPARSER_H

class MessageStream;
class MsgStreamModel;
class MsgStorage;
class SendMessages;
class SendMsgModel;
class Msg;
class MessageConfig;
class IDModel;
class IDRep;
class MsgTypeModel;
class MsgTypeRep;
class MessageFilter;
class FilterIDStore;
class FilterCodeStore;
class FilterTimestampStore;
class SystemOverview;
class SysOvrvObject;
class SysOvrvTextLabel;
class SysOvrvTrigger;
class ErrorLogView;
class ErrLogModel;
class ErrorLogEntry;

class FileParser
{
public:
    FileParser(){}
    virtual ~FileParser(){}

    virtual void visit(MessageStream &visitor) = 0;
    virtual void visit(MsgStreamModel &visitor) = 0;
    virtual void visit(MsgStorage &visitor) = 0;
    virtual void visit(SendMessages &visitor) = 0;
    virtual void visit(SendMsgModel &visitor) = 0;
    virtual void visit(Msg &visitor) = 0;
    virtual void visit(MessageConfig &visitor) = 0;
    virtual void visit(IDModel &visitor) = 0;
    virtual void visit(IDRep &visitor) = 0;
    virtual void visit(MsgTypeModel &visitor) = 0;
    virtual void visit(MsgTypeRep &visitor) = 0;
    virtual void visit(MessageFilter &visitor) = 0;
    virtual void visit(FilterIDStore &visitor) = 0;
    virtual void visit(FilterCodeStore &visitor) = 0;
    virtual void visit(FilterTimestampStore &visitor) = 0;
    virtual void visit(SystemOverview &visitor) = 0;
    virtual void visit(SysOvrvObject &visitor) = 0;
    virtual void visit(SysOvrvTextLabel &visitor) = 0;
    virtual void visit(SysOvrvTrigger &visitor) = 0;
    virtual void visit(ErrorLogView &visitor) = 0;
    virtual void visit(ErrLogModel &visitor) = 0;
    virtual void visit(ErrorLogEntry &visitor) = 0;
};

#endif /* FILEPARSER_H */
