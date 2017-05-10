/**
 * @file MsgIDFilter.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Filters #IMsg by #MsgIDType
 */
#ifndef MSGIDFILTER_H
#define MSGIDFILTER_H

#include <QObject>

#include "IMsg.h"
#include "IMsgIDFilter.h"
#include "IMsgIDFilterStore.h"

#include "MsgIDType.h"

/**
 * @addtogroup MsgIDFilterGroup
 * 
 * @{
 */

/**
 * @brief The MsgIDFilter
 */
class MsgIDFilter : public IMsgIDFilter
{
public:
    explicit MsgIDFilter(
            IMsgIDFilterStore *msgIDFilterStore,
            QObject * parent = Q_NULLPTR
            );
    virtual ~MsgIDFilter();

    /**
     * @brief Matches the passed #IMsg against the current filter state and
     * configuration and returns the result
     * 
     * If the filter is not enabled, this function always returns true
     * 
     * @returns bool filter result
     * @retval true The #MsgIDType of the passed #IMsg is valid
     * @retval false The #MsgIDType of the passed #IMsg is invalid
     */
    virtual bool filterMessage(const IMsg &msgToFilter) const;

    virtual void enableFilter(const bool enable);
    virtual bool isFilterEnabled() const;

    virtual void invertFilter(const bool invert);
    virtual bool isFilterInverted() const;

    void addMsgIDToFilter(const MsgIDType &msgIDToAdd);
    void removeMsgIDFromFilter(const MsgIDType &msgIDToRemove);

    void applyUserRole(const UserRoleManagement::UserRole roleToApply);

private:
    bool applyInversion(const bool intermediateFilterResult) const;

private:
    IMsgIDFilterStore *msgIDFilterStore;

    bool isEnabled;
    bool isInverted;


    // IFileParsable interface
public:
    virtual void accept(FileParser *visitor);

    // IMsgIDFilter interface
public:
    virtual void clear();
};

/**
 * @}
 */

#endif /* MSGIDFILTER_H */
