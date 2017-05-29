/**
 * @file MessageFilter.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief The default implementation of #IMessageFilter
 */
#ifndef MESSAGEFILTER_H
#define MESSAGEFILTER_H

#include <QObject>
#include <QVector>
#include "IMessageFilter.h"

/**
 * @addtogroup MsgFilterGroup
 * 
 * @{
 */

/**
 * @brief The MessageFilter
 */
class MessageFilter : public IMessageFilter
{
public:
    MessageFilter(QObject *parent = Q_NULLPTR);
    virtual ~MessageFilter();

    /**
     * @brief Filters an #IMsg by all currently set message filters
     * 
     * This method invokes all #IFilter and #IMsgFilter objects that are
     * contained in the #MessageFilter
     * 
     * @returns Accumulated bool result of the filters
     * @retval true All current filters evaluate the message to be valid
     * @retval false One of the current filters evaluate the message to be
     */
    virtual bool filterMessage(const IMsg &msgToFilter) const;
    /**
     * @brief Filters an #ITimestampedMsg by all currently set timestamped
     * message filters and message filters
     * 
     * This method invokes all #ITimestampedMsgFilter objects that are
     * contained in the #MessageFilter and then passes the msgToFilter to the
     * filterMessage method that takes #IMsg to filter for message criteria.
     * 
     * @returns Accumulated bool result of the filters
     * @retval true All current filters evaluate the message to be valid
     * @retval false One of the current filters evaluate the message to be
     */
    virtual bool filterMessage(const ITimestampedMsg &msgToFilter) const;

    virtual bool filterMessageByFilter(
            IMsgFilter *filterToUse,
            const IMsg &msgToFilter
            ) const;

    virtual bool filterMessageByFilter(
            ITimestampedMsgFilter *filterToUse,
            const ITimestampedMsg &msgToFilter
            ) const;

    virtual void addFilter(IMsgFilter *filterToAdd);
    virtual void addFilter(ITimestampedMsgFilter *filterToAdd);

    virtual void removeFilter(IMsgFilter *filterToRemove);
    virtual void removeFilter(ITimestampedMsgFilter *filterToRemove);

    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);

private:
    QVector<IMsgFilter *> msgFilterStore;
    QVector<ITimestampedMsgFilter *> timestampedMsgFilterStore;
};

/**
 * @}
 */

#endif // MESSAGEFILTER_H
