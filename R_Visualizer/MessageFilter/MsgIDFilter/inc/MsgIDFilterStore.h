/**
 * @file MsgIDFilterStore.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Default implementation of #IMsgIDFilterStore
 */
#ifndef MSGIDFILTERSTORE_H
#define MSGIDFILTERSTORE_H

#include <QVector>
#include "IMsgIDFilterStore.h"

#include "MsgIDType.h"

/**
 * @brief The MsgIDFilterStore
 */
class MsgIDFilterStore : public IMsgIDFilterStore
{
public:
    MsgIDFilterStore(QObject *parent = Q_NULLPTR);
    virtual ~MsgIDFilterStore();

    /**
     * @brief Adds the specified #MsgIDType to the store
     * 
     * @note emits #sgnl_MsgIDAboutToBeAdded and #sgnl_MsgIDAdded
     */
    void addMsgID(const MsgIDType &msgIDToAdd);

    /**
     * @brief Removes the specified #MsgIDType from the store
     * 
     * @note emits #sgnl_MsgIDAboutToBeRemoved and #sgnl_MsgIDRemoved
     */
    void removeMsgID(const MsgIDType &msgIDToRemove);

    /**
     * @brief Evaluates whether the specified #MsgIDType is contained in the
     * store
     * 
     * @returns If the specified #MsgIDType is contained in the store
     * @retval true The #MsgIDType is contained in the store
     * @retval false The #MsgIDType is not contained in the store
     */
    bool containsMsgID(const MsgIDType &msgID) const;

    /**
     * @brief Returns the #MsgIDTpe at the specified index
     * 
     * @returns A const reference of the #MsgIDType at the specified index in
     * the store
     */
    const MsgIDType &at(const int index) const;

    /**
     * @brief Returns the #MsgIDTpe at the specified index
     * 
     * @returns A modifialbe reference to the #MsgIDType at the specified index
     * in the store
     * 
     * @warning Index must be valid!
     */
    MsgIDType &at(const int index);

    /**
     * @brief Returns the current size of the store
     */
    int size() const;

    /**
     * @brief Returns the index of the specified #MsgIDType in the store
     * 
     * @returns index of specified #MsgIDType
     */
    int indexOf(const MsgIDType &msgID) const;

    /**
     * @brief Clears the store removing all currently contained #MsgIDTypes
     * 
     * @note emits #sgnl_AboutToBeCleared and #sgnl_Cleared
     */
    void clear();

private:
    /**
     * @brief Vector to store the #MsgIDTypes for the #MsgIDFilterStore
     */
    QVector<MsgIDType> msgIDVector;
};

#endif /* MSGIDFILTERSTORE_H */
