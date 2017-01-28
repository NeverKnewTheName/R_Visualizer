#ifndef ISYSOVRVELEMENT_H
#define ISYSOVRVELEMENT_H


class ISysOvrvElement
{
public:
    ISysOvrvElement();
    virtual void setParent(ISysOvrvElement *parent) = 0;
};

#endif // ISYSOVRVELEMENT_H
