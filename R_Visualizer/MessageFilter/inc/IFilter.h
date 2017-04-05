#ifndef IFILTER_H
#define IFILTER_H

class IFilter
{
public:
    virtual ~IFilter(){}

    virtual void enableFilter(const bool enable) = 0;
    virtual bool isEnabled() const = 0;

    virtual void invertFilter(const bool invert) = 0;
    virtual void isInverted() const = 0;

signals:
    virtual void sgnl_filterEnabled(const bool enabled) = 0;
    virtual void sgnl_filterInverted(const bool inverted) = 0;
    virtual void sgnl_filterChanged() = 0;

public slots:
    void slt_enableFilter(const bool enable);
    void slt_invertFilter(const bool invert);
};

#endif /* IFILTER_H */
