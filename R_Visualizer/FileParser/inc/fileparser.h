#ifndef FILEPARSER_H
#define FILEPARSER_H

class Msg;
class TimestampedMsg;
/* class MsgStreamStore; */
/* class MsgStorage; */
/* class TimestampedMsgStorage; */
/* class SendMsgPackageStore; */
class MsgIDMappingStore;
class MsgIDMapping;
class MsgCodeMappingStore;
class MsgCodeMapping;
class MsgDataMappingStore;
class MsgDataMapping;
/* class MsgIDFilterStore; */
/* class MsgCodeFilterStore; */
/* class MsgTimestampFilter; */

/* class SysOvrvObject; */
/* class SysOvrvTextLabel; */
/* class SysOvrvTrigger; */
/* class ErrLogModel; */
/* class ErrorLogEntry; */

class FileParser
{
public:
    FileParser(){}
    virtual ~FileParser(){}

    virtual void visit(Msg &visitor) = 0;
    virtual void visit(TimestampedMsg &visitor) = 0;
    /* virtual void visit(MsgStreamStore &visitor) = 0; */
    /* virtual void visit(MsgStorage &visitor) = 0; */
    /* virtual void visit(TimestampedMsgStorage &visitor) = 0; */
    /* virtual void visit(SendMsgPackageStore &visitor) = 0; */
    virtual void visit(MsgIDMappingStore &visitor) = 0;
    virtual void visit(MsgIDMapping &visitor) = 0;
    virtual void visit(MsgCodeMappingStore &visitor) = 0;
    virtual void visit(MsgCodeMapping &visitor) = 0;
    virtual void visit(MsgDataMappingStore &visitor) = 0;
    virtual void visit(MsgDataMapping &visitor) = 0;
    /* virtual void visit(MsgIDFilterStore &visitor) = 0; */
    /* virtual void visit(MsgCodeFilterStore &visitor) = 0; */
    /* virtual void visit(MsgTimestampFilter &visitor) = 0; */

    /* virtual void visit(SysOvrvObject &visitor) = 0; */
    /* virtual void visit(SysOvrvTextLabel &visitor) = 0; */
    /* virtual void visit(SysOvrvTrigger &visitor) = 0; */
    /* virtual void visit(ErrLogModel &visitor) = 0; */
    /* virtual void visit(ErrorLogEntry &visitor) = 0; */
};

#endif /* FILEPARSER_H */
