/**
 * @file ISystemOverview.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The interface for the System Overview
 */
#ifndef ISYSTEMOVERVIEW_H
#define ISYSTEMOVERVIEW_H

#include <QObject>

#include <QPointF>

#include "IUserRoleManager.h"

#include <QDebug>

class ISystemOverviewObject;
class IMsg;

/**
 * @brief The ISystemOverview interface
 */
class ISystemOverview : public QObject
{
    Q_OBJECT
public:
    ISystemOverview(QObject *parent = Q_NULLPTR) : QObject(parent){}
    virtual ~ISystemOverview(){}

    virtual void receiveMsg(const IMsg &receivedMsg) = 0;
    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply) = 0;

signals:

public slots:
    virtual void slt_ReceiveMsg(const IMsg &receivedMsg)
    {
        receiveMsg(receivedMsg);
    }

    virtual void slt_RequestAddObject(const QPointF &position)
    {
        qDebug() << "Add Object Request at: " << position;
    }

    virtual void slt_RequestRemoveObject(ISystemOverviewObject *objectToRemove)
    {
        qDebug() << "Remove Object Request";
    }

    virtual void slt_RequestEditObject(ISystemOverviewObject *objectToEdit)
    {
        qDebug() << "Edit Object Request";
    }

};

#endif /* ISYSTEMOVERVIEW_H */
