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

/**
 * @brief The ISystemOverview interface
 */
class ISystemOverview
{
public:
    virtual ~ISystemOverview();

signals:

public slots:
    void slt_receiveMsg(const IMsg &receivedMsg) = 0;
    void slt_applyUserRole(const UserRoleMngr::UserRole roleToApply) = 0;
};

#endif /* ISYSTEMOVERVIEW_H */
