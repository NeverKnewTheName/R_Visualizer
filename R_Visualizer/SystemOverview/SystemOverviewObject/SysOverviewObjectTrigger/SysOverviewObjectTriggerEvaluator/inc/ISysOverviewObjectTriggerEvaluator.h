#ifndef ISYSOVERVIEWOBJECTTRIGGEREVALUATOR_H
#define ISYSOVERVIEWOBJECTTRIGGEREVALUATOR_H

#include <memory>

class IMsg;
class MessageTypeIdentifier;

class ISysOverviewObjectTriggerEvaluator
{
public:
    enum EvaluatorType
    {
        EvaluatorType_MsgTypeEvaluator,
        EvaluatorType_DSLEvaluator,
        EvaluatorType_ParserEvaluator,
        EvaluatorType_NR_OF_TYPES
    };

    virtual ~ISysOverviewObjectTriggerEvaluator(){}

    virtual ISysOverviewObjectTriggerEvaluator *clone() const = 0;

    virtual EvaluatorType getType() const = 0;

    virtual MessageTypeIdentifier getMsgType() const = 0;
    virtual void setMsgType(const MessageTypeIdentifier &msgType) = 0;

    virtual bool evaluate(const IMsg &msgToEvaluate) const = 0;

};

typedef std::unique_ptr<ISysOverviewObjectTriggerEvaluator> SysOvrvObjTriggerEvaluatorPtr;

template<class Derived>
class ISysOverviewObjectTriggerEvaluatorCRTPHelper :
        public ISysOverviewObjectTriggerEvaluator
{
public:
    virtual ISysOverviewObjectTriggerEvaluator *clone() const
    {
        return new Derived(static_cast<const Derived &>(*this));
    }
};

#endif // ISYSOVERVIEWOBJECTTRIGGEREVALUATOR_H
