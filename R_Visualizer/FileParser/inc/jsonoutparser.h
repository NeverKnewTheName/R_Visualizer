#ifndef JSONOUTPARSER_H
#define JSONOUTPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <memory>

#include "fileparser.h"

class JsonOutParser : public FileParser
{
public:
    JsonOutParser();
    ~JsonOutParser();

    QJsonDocument getJsonDocument() const;

    /* void visit(MessageStream &visitor); */
    void visit(MsgStreamModel &visitor);
    void visit(MsgStorage &visitor);
    void visit(TimestampedMsgStorage &visitor);
    /* void visit(SendMessages &visitor); */
    void visit(SendMsgModel &visitor);
    void visit(Msg &visitor);
    void visit(TimestampedMsg &visitor);
    /* void visit(MessageConfig &visitor); */
    /* void visit(IDModel &visitor); */
    void visit(MsgIDRep &visitor);
    /* void visit(MsgTypeModel &visitor); */
    void visit(MsgCodeRep &visitor);
    void visit(MsgDataRep &visitor);
    /* void visit(MessageFilter &visitor); */
    void visit(FilterIDStore &visitor);
    void visit(FilterCodeStore &visitor);
    void visit(FilterTimestampStore &visitor);
    /* void visit(SystemOverview &visitor); */
    void visit(SysOvrvObject &visitor);
    void visit(SysOvrvTextLabel &visitor);
    void visit(SysOvrvTrigger &visitor);
    /* void visit(ErrorLogView &visitor); */
    void visit(ErrLogModel &visitor);
    void visit(ErrorLogEntry &visitor);

private:
    std::unique_ptr<QJsonValue> currentJsonValuePtr;

};

#endif /* JSONOUTPARSER_H */
