/**
 * @file IMsgIDFilterStore.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Interface for #MsgIDType storages
 */
#ifndef IMSGIDFILTERSTORE_H
#define IMSGIDFILTERSTORE_H

#include <QObject>

#include "MsgIDType.h"
#include "IFileParsable.h"

/**
 * @addtogroup MsgIDFilterGroup
 * 
 * @{
 */

/**
 * @brief The IMsgIDFilterStore interface
 */
class IMsgIDFilterStore : public QObject, public IFileParsable
{
    Q_OBJECT
public:
    IMsgIDFilterStore(QObject *parent = Q_NULLPTR) : QObject(parent){}
    virtual ~IMsgIDFilterStore(){}

    /**
     * @brief Adds the specified #MsgIDType to the store
     * 
     * @note must emit #sgnl_MsgIDAboutToBeAdded and #sgnl_MsgIDAdded
     */
    virtual void addMsgID(const MsgIDType &msgIDtoAdd) = 0;
    /**
     * @brief Removes the specified #MsgIDType from the store
     * 
     * @note must emit #sgnl_MsgIDAboutToBeRemoved and #sgnl_MsgIDRemoved
     */
    virtual void removeMsgID(const MsgIDType &msgIDtoRemove) = 0;

    /**
     * @brief Evaluates whether the specified #MsgIDType is contained in the
     * store
     * 
     * @returns If the specified #MsgIDType is contained in the store
     * @retval true The #MsgIDType is contained in the store
     * @retval false The #MsgIDType is not contained in the store
     */
    virtual bool containsMsgID(const MsgIDType &msgID) const = 0;

    /**
     * @brief Returns the #MsgIDType at the specified index
     * 
     * @returns A const reference of the #MsgIDType at the specified index in
     * the store
     */
    virtual const MsgIDType &at(const int index) const = 0;

    /**
     * @brief Returns the #MsgIDType at the specified index
     * 
     * @returns A modifialbe reference to the #MsgIDType at the specified index
     * in the store
     */
    virtual MsgIDType &at(const int index) = 0;

    /**
     * @brief Returns the current size of the store
     */
    virtual int size() const = 0;

    /**
     * @brief Returns the index of the specified #MsgIDType in the store
     * 
     * @returns index of specified #MsgIDType
     */
    virtual int indexOf(const MsgIDType &msgID) const = 0;

    /**
     * @brief Clears the store removing all currently contained #MsgIDType
     * 
     * @note Must emit #sgnl_AboutToBeCleared and #sgnl_Cleared
     */
    virtual void clear() = 0;

signals:
    /**
     * @brief Signal is emitted when a #MsgIDType is about to be added to the
     * store
     */
    void sgnl_MsgIDAboutToBeAdded(
            const MsgIDType &msgIDToAdd
            );

    /**
     * @brief Signal is emitted when a #MsgIDType has been added to the store
     */
    void sgnl_MsgIDAdded(
            const MsgIDType &msgIDToAdd
            );

    /**
     * @brief Signal is emitted when a #MsgIDType is about to be removed from
     * the store
     */
    void sgnl_MsgIDAboutToBeRemoved(
            const MsgIDType &msgIDToRemove
            );

    /**
     * @brief Signal is emitted when a #MsgIDType has been removed from the
     * store
     */
    void sgnl_MsgIDRemoved(
            const MsgIDType &msgIDToRemove
            );

    /**
     * @brief Signal is emitted when the store is about to be cleared
     */
    void sgnl_AboutToBeCleared();

    /**
     * @brief Signal is emitted when the store has been cleared
     */
    void sgnl_Cleared();

    /**
     * @brief Signal is emitted when the store has been changed
     */
    void sgnl_HasChanged();

public slots:
    /**
     * @brief Slot that adds the specified #MsgIDType to the store
     * 
     * @note Calls #addMsgID
     */
    void slt_AddMsgIDToFilter(
            const MsgIDType &msgIDToAdd
            )
    {
        addMsgID(msgIDToAdd);
    }

    /**
     * @brief Slot that removes the specified #MsgIDType from the store
     * 
     * @note Calls #removeMsgID
     */
    void slt_RemoveMsgIDFromFilter(
            const MsgIDType &msgIDToRemove
            )
    {
        removeMsgID(msgIDToRemove);
    }

    /**
     * @brief Slot that clears the store
     * 
     * @note Calls #clear
     */
    void slt_ClearStore()
    {
        clear();
    }
};

/**
 * @}
 */

#endif /* IMSGIDFILTERSTORE_H */
