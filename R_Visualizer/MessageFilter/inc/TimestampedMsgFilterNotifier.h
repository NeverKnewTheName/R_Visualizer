/**
 * @file TimestampedMsgFilterNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-21
 * 
 * @brief Signal and slot handler for #ITimestampedMsgFilter
 */
#ifndef TIMESTAMPEDMSGFILTERNOTIFIER_H
#define TIMESTAMPEDMSGFILTERNOTIFIER_H

#include <QObject>

#include "userrolemngs.h"

class ITimestampedMsgFilter;

/**
 * @brief The TimestampedMsgFilterNotifier
 */
class TimestampedMsgFilterNotifier : public QObject
{
    Q_OBJECT
public:
    TimestampedMsgFilterNotifier(
            ITimestampedMsgFilter *filterToNotify,
            QObject *parent = Q_NULLPTR
            );
    virtual ~TimestampedMsgFilterNotifier();

    virtual void emitSgnlFilterEnabled(const bool enabled);
    virtual void emitSgnlFilterInverted(const bool inverted);
    virtual void emitSgnlFilterChanged(IMsgFilter *filterThatHasChanged);

signals:

    void sgnl_FilterEnabled(const bool enabled);
    void sgnl_FilterInverted(const bool inverted);
    void sgnl_FilterChanged(ITimestampedMsgFilter *filterThatHasChanged);

public slots:

    void slt_enableFilter(const bool enable);
    void slt_invertFilter(const bool invert);
    void slt_applyUserRole(const UserRoleMngr::UserRole roleToApply);

private:
    ITimestampedMsgFilter *filterToNotify;
};

#endif /* TIMESTAMPEDMSGFILTERNOTIFIER_H */
