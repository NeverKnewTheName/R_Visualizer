#ifndef FILEPARSER_H
#define FILEPARSER_H

class IMsg;
class ITimestampedMsg;
class IMsgStreamStore;
class MsgStorage;
class TimestampedMsgStorage;
class ISendMsgPackageStore;
class IMsgIDMappingStore;
class IMsgIDMapping;
class IMsgCodeMappingStore;
class IMsgCodeMapping;
class IMsgDataMappingStore;
class IMsgDataMapping;
class IMsgIDFilterStore;
class IMsgCodeFilterStore;
class IMsgTimespanFilter;

class ISystemOverviewObject;
class ISysOverviewObjectManager;
class ISysOverviewObjectColorManager;
class ISysOverviewObjectResizeManager;
class SysOverviewTextLabel;
class ISysOverviewObjectTrigger;
class ISysOverviewLabelTrigger;
class ISysOverviewObjectTriggerEvaluator;

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

    virtual void visit(IMsg &visitor) = 0;
    virtual void visit(ITimestampedMsg &visitor) = 0;
    virtual void visit(IMsgStreamStore &visitor) = 0;
    virtual void visit(MsgStorage &visitor) = 0;
    virtual void visit(TimestampedMsgStorage &visitor) = 0;
    virtual void visit(ISendMsgPackageStore &visitor) = 0;
    virtual void visit(IMsgIDMappingStore &visitor) = 0;
    virtual void visit(IMsgIDMapping &visitor) = 0;
    virtual void visit(IMsgCodeMappingStore &visitor) = 0;
    virtual void visit(IMsgCodeMapping &visitor) = 0;
    virtual void visit(IMsgDataMappingStore &visitor) = 0;
    virtual void visit(IMsgDataMapping &visitor) = 0;
    virtual void visit(IMsgIDFilterStore &visitor) = 0;
    virtual void visit(IMsgCodeFilterStore &visitor) = 0;
    virtual void visit(IMsgTimespanFilter &visitor) = 0;

    virtual void visit(ISystemOverviewObject &visitor) = 0;
    virtual void visit(ISysOverviewObjectManager &visitor) = 0;
    virtual void visit(ISysOverviewObjectColorManager &visitor) = 0;
    virtual void visit(ISysOverviewObjectResizeManager &visitor) = 0;
    virtual void visit(SysOverviewTextLabel &visitor) = 0;
    virtual void visit(ISysOverviewObjectTrigger &visitor) = 0;
    virtual void visit(ISysOverviewLabelTrigger &visitor) = 0;
    virtual void visit(ISysOverviewObjectTriggerEvaluator &visitor) = 0;

    /* virtual void visit(SysOvrvObject &visitor) = 0; */
    /* virtual void visit(SysOvrvTextLabel &visitor) = 0; */
    /* virtual void visit(SysOvrvTrigger &visitor) = 0; */
    /* virtual void visit(ErrLogModel &visitor) = 0; */
    /* virtual void visit(ErrorLogEntry &visitor) = 0; */
};

#endif /* FILEPARSER_H */
