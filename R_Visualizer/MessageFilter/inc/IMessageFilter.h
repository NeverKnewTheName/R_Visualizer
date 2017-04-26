/**
 * @file IMessageFilter.h
 * @author Christian Neuberger
 * @date 2017-04-05
 * 
 * @brief The #IMessageFilter provides an interface for the message filter
 * module
 */
#ifndef IMESSAGEFILTER_H
#define IMESSAGEFILTER_H

#include <QObject>


#include "IUserRoleManager.h"

class IFilter;
class IMsgFilter;
class ITimestampedMsgFilter;

class IMsg;
class ITimestampedMsg;

/**
 * @defgroup MsgFilterGroup Message Filter
 * 
 * Every class that is related to the Message Filter
 * 
 * @{
 */

/**
 * @brief The #IMessageFilter interface
 */
class IMessageFilter : public QObject
{
    Q_OBJECT
public:
    IMessageFilter(QObject *parent = Q_NULLPTR) : QObject(parent){}
    virtual ~IMessageFilter(){}

    /**
     * @brief Apply the #IMessageFilter to an #IMsg
     * 
     * @note This filtering ignores timestamp properties and does only filter
     * fields contained in the #IMsg interface.
     */
    virtual bool filterMessage(const IMsg &msgToFilter) const = 0;
    /**
     * @brief Apply the #IMessageFilter to an #ITimestampedMsg
     * 
     * @returns bool filter result
     * @retval true All current filters evaluate the message to be valid
     * @retval false One of the current filters evaluate the message to be
     * invalid
     */
    virtual bool filterMessage(const ITimestampedMsg &msgToFilter) const = 0;

    /**
     * @brief Filter the given msgToFilter with the given filterToUse
     * 
     * @param[in] filterToUse Filter that shall be used to evaluate the message
     * @param[in] msgToFilter Message that shall be evaluated by the filter
     * 
     * @returns bool filter result
     * @retval true The given filter evaluates the message to be valid
     * @retval false The given filter evaluates the message to be invalid
     */
    virtual bool filterMessageByFilter(
            IMsgFilter *filterToUse,
            const IMsg &msgToFilter
            ) const = 0;

    /**
     * @brief Filter the given msgToFilter with the given filterToUse
     * 
     * @param[in] filterToUse Filter that shall be used to evaluate the message
     * @param[in] msgToFilter Message that shall be evaluated by the filter
     * 
     * @returns bool filter result
     * @retval true The given filter evaluates the message to be valid
     * @retval false The given filter evaluates the message to be invalid
     */
    virtual bool filterMessageByFilter(
            ITimestampedMsgFilter *filterToUse,
            const ITimestampedMsg &msgToFilter
            ) const = 0;

    /**
     * @brief Method to add an #IMsgFilter
     * 
     * @note This overload is supposed to provide implementations with the
     * means to serve #IMsgFilter separately from #ITimestampedMsgFilter and
     * the more general #IFilter. For instance, an implementation could contain
     * different lists of filters for #IMsgFilter, #ITimestampedMsgFilter, and
     * #IFilter filters. These can then be treated differently.
     */
    virtual void addFilter(IMsgFilter *filterToAdd) = 0;
    /**
     * @brief Method to add an #ITimestampedMsgFilter
     * 
     * @note This overload is supposed to provide implementations with the
     * means to serve #ITimestampedMsgFilter separately from #IMsgFilter and
     * the more general #IFilter. For instance, an implementation could contain
     * different lists of filters for #ITimestampedMsgFilter, #IMsgFilter, and
     * #IFilter filters. These can then be treated differently.
     */
    virtual void addFilter(ITimestampedMsgFilter *filterToAdd) = 0;

    /**
     * @brief Method to remove an #IMsgFilter
     * 
     * @note This overload is supposed to provide implementations with the
     * means to serve #ITimestampedMsgFilter separately from #IMsgFilter and
     * the more general #IFilter. For instance, an implementation could contain
     * different lists of filters for #ITimestampedMsgFilter, #IMsgFilter, and
     * #IFilter filters. These can then be searched more efficiently.
     */
    virtual void removeFilter(IMsgFilter *filterToAdd) = 0;
    /**
     * @brief Method to remove an #ITimestampedMsgFilter
     * 
     * @note This overload is supposed to provide implementations with the
     * means to serve #ITimestampedMsgFilter separately from #IMsgFilter and
     * the more general #IFilter. For instance, an implementation could contain
     * different lists of filters for #ITimestampedMsgFilter, #IMsgFilter, and
     * #IFilter filters. These can then be searched more efficiently.
     */
    virtual void removeFilter(ITimestampedMsgFilter *filterToAdd) = 0;

    virtual void applyUserRole(
            const UserRoleManagement::UserRole roleToApply
            ) = 0;

signals:
    void sgnl_MsgFilterHasChanged(
            const IMsgFilter &filterThatHasChanged
            );

    void sgnl_TimestampFilterHasChanged(
            const ITimestampedMsgFilter &filterThatHasChanged
            );

public slots:
    virtual void slt_ApplyRole(const UserRoleManagement::UserRole roleToApply)
    {
        applyUserRole(roleToApply);
    }

};

/**
 * @}
 */
#endif /* IMESSAGEFILTER_H */
