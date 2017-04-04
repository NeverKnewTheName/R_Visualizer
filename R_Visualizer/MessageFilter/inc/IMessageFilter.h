#ifndef IMESSAGEFILTER_H
#define IMESSAGEFILTER_H

#include "IMsg.h"

class IMessageFilter
{
public:
    virtual ~IMessageFilter();

    virtual bool filterMessage(const IMsg &msgToFilter) const = 0;

    virtual void addFilter(IFilter *filterToAdd) = 0;
    virtual void removeFilter(IFilter *filterToRemove) = 0;

signals:
    virtual void sgnl_FilterChanged() = 0;
    virtual void sgnl_PropagateUserRole(
            const UserRoleMngr::UserRole roleToApply
            ) = 0;

public slots:
    virtual void slt_applyRole(
            const UserRoleMngr::UserRole roleToApply
            ) = 0;

};

#endif /* IMESSAGEFILTER_H */
