/**
 * \file sysovrvobjderivationhelper.h
 * \author Christian Neuberger
 * \date 2017-02-20
 * 
 * \brief CRTP Helper class for #SysOvrvObject derivations
 */
#ifndef SYSOVRVOBJDERIVATIONHELPER_H
#define SYSOVRVOBJDERIVATIONHELPER_H

#include "sysovrvobject.h"

template<class Derived>
class SysOvrvObjDerivationHelper : public SysOvrvObject
{
public:
    //Normal constructor
    SysOvrvObjDerivationHelper(QGraphicsItem *parent = Q_NULLPTR) : SysOvrvObject(parent){}
    //Copy constructor
    SysOvrvObjDerivationHelper(const SysOvrvObject &other) : SysOvrvObject(other){}
    //Move constructor
    SysOvrvObjDerivationHelper(SysOvrvObject &&other) : SysOvrvObject(std::move(other)){}

    virtual SysOvrvObject *clone() const
    {
        return new Derived(static_cast<const Derived &>(*this));
    }
    virtual SysOvrvObject *move()
    {
        return new Derived(static_cast<Derived &&>(*this));
    }
};

#endif /* SYSOVRVOBJDERIVATIONHELPER_H */
