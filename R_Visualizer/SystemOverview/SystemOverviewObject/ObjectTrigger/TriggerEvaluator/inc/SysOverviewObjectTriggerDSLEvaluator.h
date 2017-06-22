#ifndef SYSOVERVIEWOBJECTTRIGGERDSLEVALUATOR_H
#define SYSOVERVIEWOBJECTTRIGGERDSLEVALUATOR_H

#include <QString>
#include "ISysOverviewObjectTriggerEvaluator.h"
#include "MessageTypeIdentifier.h"

class SysOverviewObjectTriggerDSLEvaluator :
        public ISysOverviewObjectTriggerEvaluatorCRTPHelper<SysOverviewObjectTriggerDSLEvaluator>
{
public:
    SysOverviewObjectTriggerDSLEvaluator();
    SysOverviewObjectTriggerDSLEvaluator(
            const MessageTypeIdentifier &msgType,
            const QString &formatString = QString("")
            );

    virtual ~SysOverviewObjectTriggerDSLEvaluator();



    // ISysOverviewObjectTriggerEvaluator interface
public:
    virtual EvaluatorType getType() const;
    virtual MessageTypeIdentifier getMsgType() const;
    virtual void setMsgType(const MessageTypeIdentifier &msgType);
    virtual bool evaluate(const IMsg &msgToEvaluate) const;
    virtual QString evaluateToString(const IMsg &msgToEvaluate) const;

    QString getFormatString() const;
    void setFormatString(const QString &value);

private:
    MessageTypeIdentifier msgType;
    QString formatString;
};

#endif // SYSOVERVIEWOBJECTTRIGGERDSLEVALUATOR_H
