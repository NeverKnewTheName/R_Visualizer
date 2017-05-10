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

private:
    std::unique_ptr<QJsonValue> currentJsonValuePtr;

};

#endif /* JSONINPARSER_H */
