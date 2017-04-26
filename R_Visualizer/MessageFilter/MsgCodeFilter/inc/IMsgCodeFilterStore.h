/**
 * @file IMsgCodeFilterStore.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Interface for #MsgCodeType storages
 */
#ifndef IMSGCODEFILTERSTORE_H
#define IMSGCODEFILTERSTORE_H

#include <QObject>

#include "MsgCodeType.h"

/**
 * @addtogroup MsgCodeFilterGroup
 * 
 * @{
 */

/**
 * @brief The IMsgCodeFilterStore interface
 */
class IMsgCodeFilterStore : public QObject
{
    Q_OBJECT
public:
    IMsgCodeFilterStore(QObject *parent = Q_NULLPTR) : QObject(parent){}
    virtual ~IMsgCodeFilterStore(){}

    virtual void addMsgCode(const MsgCodeType &msgCodeToAdd) = 0;
    virtual void removeMsgCode(const MsgCodeType &msgCodeToRemove) = 0;

    virtual bool containsMsgCode(const MsgCodeType &msgCode) const = 0;

    virtual const MsgCodeType &at(const int index) const = 0;
    virtual MsgCodeType &at(const int index) = 0;

    /**
     * @brief Returns the current size of the store
     */
    virtual int size() const = 0;

    /**
     * @brief Returns the index of the specified #MsgCodeType in the store
     */
    virtual int indexOf(const MsgCodeType &msgCode) const = 0;

    /**
     * @brief Clears the store removing all conteind #MsgCodeType
     */
    virtual void clear() = 0;

signals:
    /**
     * @brief Signal is emitted when a #MsgCodeType is about to be added to the
     * store
     */
    void sgnl_MsgCodeAboutToBeAdded(
            const MsgCodeType &msgCodeToAdd
            );

    /**
     * @brief Signal is emitted when a #MsgCodeType has been added to the store
     */
    void sgnl_MsgCodeAdded(
            const MsgCodeType &msgCodeToAdd
            );

    /**
     * @brief Signal is emitted when a #MsgCodeType is about to be removed from
     * the store
     */
    void sgnl_MsgCodeAboutToBeRemoved(
            const MsgCodeType &msgCodeToRemove
            );

    /**
     * @brief Signal is emitted when a #MsgCodeType has been removed from the
     * store
     */
    void sgnl_MsgCodeRemoved(
            const MsgCodeType &msgCodeToRemove
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
     * @brief Slot that adds the specified #MsgCodeType to the store
     * 
     * @note Calls #addMsgCode
     */
    void slt_AddMsgCodeToFilter(
            const MsgCodeType &msgCodeToAdd
            )
    {
        addMsgCode(msgCodeToAdd);
    }

    /**
     * @brief Slot that removes the specified #MsgCodeType from the store
     * 
     * @note Calls #removeMsgCode
     */
    void slt_RemoveMsgCodeFromFilter(
            const MsgCodeType &msgCodeToRemove
            )
    {
        removeMsgCode(msgCodeToRemove);
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

#endif /* IMSGCODEFILTERSTORE_H */
