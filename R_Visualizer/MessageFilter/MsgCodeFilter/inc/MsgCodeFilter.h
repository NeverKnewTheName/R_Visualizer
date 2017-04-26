/**
 * @file MsgCodeFilter.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Filters #Imsg by #MsgCodeType
 */
#ifndef MSGCODEFILTER_H
#define MSGCODEFILTER_H

#include <QObject>

#include "IMsg.h"
#include "IMsgCodeFilter.h"
#include "IMsgCodeFilterStore.h"

#include "MsgCodeType.h"

/**
 * @addtogroup MsgCodeFilterGroup
 * 
 * @{
 */

/**
 * @brief The MsgCodeFilter
 */
class MsgCodeFilter : public IMsgCodeFilter
{
    Q_OBJECT
public:
    MsgCodeFilter(
            IMsgCodeFilterStore *msgCodeFilterStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeFilter();

    /**
     * @brief Matches the passed #IMsg against the current filter state and
     * configuration and returns the result
     * 
     * If the filter is not enabled, this function always returns true
     * 
     * @returns bool filter result
     * @retval true The #MsgCodeType of the passed #IMsg is valid
     * @retval false The #MsgCodeType of the passed #IMsg is invalid
     */
    virtual bool filterMessage(const IMsg &msgToFilter) const;

    virtual void enableFilter(const bool enable);
    virtual bool isFilterEnabled() const;

    virtual void invertFilter(const bool invert);
    virtual bool isFilterInverted() const;

    void addMsgCodeToFilter(const MsgCodeType &msgCodeToAdd);
    void removeMsgCodeFromFilter(const MsgCodeType &msgCodeToRemove);

    void applyUserRole(const UserRoleManagement::UserRole roleToApply);

private:
    bool applyInversion(const bool intermediateFilterResult) const;

private:
    IMsgCodeFilterStore *msgCodeFilterStore;

    bool isEnabled;
    bool isInverted;

};

/**
 * @}
 */

#endif /* MSGCODEFILTER_H */
