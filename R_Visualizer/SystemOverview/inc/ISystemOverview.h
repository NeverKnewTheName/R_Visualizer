/**
 * @file ISystemOverview.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The interface for the System Overview
 */
#ifndef ISYSTEMOVERVIEW_H
#define ISYSTEMOVERVIEW_H

#include "userrolemngr.h"

class SystemOverviewNotifier;
class IMsg;

/**
 * @brief The ISystemOverview interface
 */
class ISystemOverview
{
public:
    virtual ~ISystemOverview(){}

    virtual void receiveMsg(const IMsg &receivedMsg) = 0;
    virtual void applyUserRole(const UserRoleMngr::UserRole roleToApply) = 0;

    virtual SystemOverviewNotifier *getNotifier() = 0;
};

#endif /* ISYSTEMOVERVIEW_H */
