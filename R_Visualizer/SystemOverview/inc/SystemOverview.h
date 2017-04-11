/**
 * @file SystemOverview.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The SystemOverview
 */
#ifndef SYSTEMOVERVIEW_H
#define SYSTEMOVERVIEW_H

#include <QObject>
#include "ISystemOverview.h"

/**
 * @brief The SystemOverview
 */
class SystemOverview : public QObject, public ISystemOverview
{
    Q_OBJECT
public:
    explicit SystemOverview(QObject *parent = 0);

signals:

public slots:
    void slt_receiveMsg(const IMsg &receivedMsg);
    void slt_applyUserRole(const UserRoleMngr::UserRole roleToApply);
};

#endif // SYSTEMOVERVIEW_H
