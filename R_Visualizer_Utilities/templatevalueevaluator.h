#ifndef TEMPLATEVALUEEVALUATOR_H
#define TEMPLATEVALUEEVALUATOR_H

#include <QString>

class TemplateValueEvaluator
{
public:
    typedef enum  {
        LimitEvaluator,
        RangeEvaluator,
        NrOfEvaluatorTypes
    } EvaluatorType;

    TemplateValueEvaluator(){}
    virtual ~TemplateValueEvaluator(){}
    virtual bool evaluate(int curValue) = 0;

    virtual QString printName() const = 0;
    virtual QString printFunction() const = 0;

    virtual EvaluatorType getEvalType() const = 0;
};



class SysOvrvTriggerLimitEvaluator : public TemplateValueEvaluator
{
public:
    typedef enum
    {
        IsEqual,
        IsEqualOrGreater,
        IsEqualOrLower,
        IsGreater,
        IsLower
    } LimitEvaluatorOperation;

    SysOvrvTriggerLimitEvaluator(int limit, LimitEvaluatorOperation evalOp = IsGreater) :
        TemplateValueEvaluator(),
        limit(limit),
        evalOp(evalOp)
    {}

    virtual bool evaluate(int curValue) override
    {
        switch(evalOp)
        {
        case IsEqual:
            return (curValue == limit);
            break;
        case IsEqualOrGreater:
            return (curValue >= limit);
            break;
        case IsEqualOrLower:
            return (curValue <= limit);
            break;
        case IsGreater:
            return (curValue > limit);
            break;
        case IsLower:
            return (curValue < limit);
            break;
        default:
            return false;
        }
    }

    virtual EvaluatorType getEvalType() const
    {
        return LimitEvaluator;
    }

    virtual QString printName() const override
    {
        return QString("LimitEvaluator");
    }
    virtual QString printFunction() const override
    {
        QString opName;

        switch(evalOp)
        {
        case IsEqual:
            opName = QString("is equal to");
            break;
        case IsEqualOrGreater:
            opName = QString("is equal to or greater than");
            break;
        case IsEqualOrLower:
            opName = QString("is equal to or lower than");
            break;
        case IsGreater:
            opName = QString("is greather than");
            break;
        case IsLower:
            opName = QString("is lower than");
            break;
        default:
            return false;
        }
        return QString("Triggered if Value %1 %2").arg(opName).arg(QString::number(limit));
    }

    LimitEvaluatorOperation getEvalOp() const
    {
        return evalOp;
    }

    void setEvalOp(const LimitEvaluatorOperation &value)
    {
        evalOp = value;
    }

    int getLimit() const
    {
        return limit;
    }
    void setLimit(int value)
    {
        limit = value;
    }

private:
    int limit;
    LimitEvaluatorOperation evalOp;
};


class SysOvrvTriggerRangeEvaluator : public TemplateValueEvaluator
{
public:
    typedef enum
    {
        IsInRange,
        IsOutOfRange
    } RangeEvaluatorOperation;
    SysOvrvTriggerRangeEvaluator(int lowerBoundary, int upperBoundary, RangeEvaluatorOperation evalOp = IsInRange, bool includeMargins = false) :
        TemplateValueEvaluator(),
        lowerBoundary(lowerBoundary),
        upperBoundary(upperBoundary),
        includeMargins(includeMargins),
        evalOp(evalOp)
    {}

    virtual bool evaluate(int curValue) override
    {
        if(includeMargins)
        {
            if((curValue == lowerBoundary) || (curValue == upperBoundary))
                return true;
        }
        switch(evalOp)
        {
        case IsInRange:
            return ((curValue > lowerBoundary) && (curValue < upperBoundary));
            break;
        case IsOutOfRange:
            return ((curValue < lowerBoundary) && (curValue > upperBoundary));
            break;
        default:
            return false;
        }
    }

    virtual QString printName() const override
    {
        return QString("RangeEvaluator");
    }

    virtual QString printFunction() const override
    {
        QString opName;
        QString marginValues = QString("margin values ");
        if(this->includeMargins)
        {
            marginValues.append("included");
        }
        else
        {
            marginValues.append("excluded");
        }
        switch(evalOp)
        {
        case IsInRange:
            opName = QString("is in the range of");
            break;
        case IsOutOfRange:
            opName = QString("is out of the range ");
            break;
        default:
            return false;
        }
        return QString("Triggered if Value %1 %2 and %3 (%4)").arg(opName).arg(QString::number(lowerBoundary)).arg(QString::number(upperBoundary)).arg(marginValues);
    }

    virtual EvaluatorType getEvalType() const
    {
        return RangeEvaluator;
    }
    RangeEvaluatorOperation getEvalOp() const
    {
        return evalOp;
    }

    void setEvalOp(const RangeEvaluatorOperation &value)
    {
        evalOp = value;
    }

    int getLowerBoundary() const
    {
        return lowerBoundary;
    }
    void setLowerBoundary(int value)
    {
        lowerBoundary = value;
    }

    int getUpperBoundary() const
    {
        return upperBoundary;
    }
    void setUpperBoundary(int value)
    {
        upperBoundary = value;
    }

private:
    int lowerBoundary;
    int upperBoundary;
    bool includeMargins;
    RangeEvaluatorOperation evalOp;
};

#endif // TEMPLATEVALUEEVALUATOR_H
