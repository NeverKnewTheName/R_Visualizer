/**
 * @file MsgFilterNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-21
 * 
 * @brief Signal and slot handler for #IMsgFilter
 */
#ifndef MSGFILTERNOTIFIER_H
#define MSGFILTERNOTIFIER_H

#include <QObject>
#include "userrolemngr.h"

class IMsgFilter;

/**
 * @brief The MsgFilterNotifier
 */
class MsgFilterNotifier : public QObject
{
    Q_OBJECT
public:
    MsgFilterNotifier(
            IMsgFilter *filterToNotify,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgFilterNotifier();

    virtual void emitSgnlFilterEnabled(const bool enabled);
    virtual void emitSgnlFilterInverted(const bool inverted);
    virtual void emitSgnlFilterChanged(IMsgFilter *filterThatHasChanged);

signals:

    void sgnl_FilterEnabled(const bool enabled);
    void sgnl_FilterInverted(const bool inverted);
    void sgnl_FilterChanged(IMsgFilter *filterThatHasChanged);

public slots:

    void slt_enableFilter(const bool enable);
    void slt_invertFilter(const bool invert);
    void slt_applyUserRole(const UserRoleMngr::UserRole roleToApply);

private:
    IMsgFilter *filterToNotify;
};

#endif /* MSGFILTERNOTIFIER_H */
