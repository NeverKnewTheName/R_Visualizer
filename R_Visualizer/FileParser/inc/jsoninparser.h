/**
 * @file jsoninparser.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief Visitor parser to parse objects from json
 */
#ifndef JSONINPARSER_H
#define JSONINPARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "fileparser.h"

#include <memory>

/**
 * @brief The JsonInParser
 */
class JsonInParser : public FileParser
{
public:
    JsonInParser();
    ~JsonInParser();

    void setJsonDocument(const QJsonDocument &jsonDoc);

    virtual void visit(Msg &visitor);
    virtual void visit(TimestampedMsg &visitor);
    virtual void visit(MsgStreamStore &visitor);
    virtual void visit(MsgStorage &visitor);
    virtual void visit(TimestampedMsgStorage &visitor);
    virtual void visit(SendMsgPackageStore &visitor);
    virtual void visit(MsgIDMappingStore &visitor);
    virtual void visit(MsgIDRep &visitor);
    virtual void visit(MsgCodeMappingStore &visitor);
    virtual void visit(MsgCodeRep &visitor);
    virtual void visit(MsgDataMappingStore &visitor);
    virtual void visit(MsgDataRep &visitor);
    virtual void visit(MsgIDFilterStore &visitor);
    virtual void visit(MsgCodeFilterStore &visitor);
    virtual void visit(MsgTimestampFilter &visitor);
    /* virtual void visit(SysOvrvObject &visitor); */
    /* virtual void visit(SysOvrvTextLabel &visitor); */
    /* virtual void visit(SysOvrvTrigger &visitor); */
    /* virtual void visit(ErrLogModel &visitor); */
    /* virtual void visit(ErrorLogEntry &visitor); */

private:
    std::unique_ptr<QJsonValue> currentJsonValuePtr;

};

#endif /* JSONINPARSER_H */
