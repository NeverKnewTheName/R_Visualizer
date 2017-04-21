#ifndef MESSAGEFILTERNOTIFIER_H
#define MESSAGEFILTERNOTIFIER_H

#include <QObject>

#include "IUserRoleManager.h"

class IMessageFilter;
class IMsgFilter;
class ITimestampedMsgFilter;

class MessageFilterNotifier : public QObject
{
    Q_OBJECT
public:
    MessageFilterNotifier(
            IMessageFilter *msgFilter,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MessageFilterNotifier();

    virtual void emitSnglMsgFilterChanged(
            IMsgFilter *filterThatHasChanged
            );

    virtual void emitSnglTimestampedMsgFilterChanged(
            ITimestampedMsgFilter *filterThatHasChanged
            );

signals:
    void sgnl_MsgFilterChanged(IMsgFilter *filterThatHasChanged);
    void sgnl_TimestampedMsgFilterChanged(
            ITimestampedMsgFilter *filterThatHasChanged
            );
    void sgnl_PropagateUserRole(
            const UserRoleManagement::UserRole roleToApply
            );

public slots:
    void slt_applyRole(
            const UserRoleManagement::UserRole roleToApply
            );

private:
    IMessageFilter *msgFilter;
};

#endif /* MESSAGEFILTERNOTIFIER_H */
