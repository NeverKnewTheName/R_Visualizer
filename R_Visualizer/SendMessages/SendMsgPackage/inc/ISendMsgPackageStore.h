/**
 * @file ISendMsgPackageStore.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The interface for message package stores
 */
#ifndef ISENDMSGPACKAGESTORE_H
#define ISENDMSGPACKAGESTORE_H

#include <QObject>

#include "IMsg.h"

/**
 * @brief The ISendMsgPackageStore interface
 */
class ISendMsgPackageStore : public QObject
{
    Q_OBJECT
public:
    ISendMsgPackageStore(QObject *parent = Q_NULLPTR) : QObject(parent){}
    virtual ~ISendMsgPackageStore(){}

    /**
     * @brief Appends the given message to the store
     * 
     * The msgToAppend can be left empty to construct a default #IPrettyMsg
     * derivate. A mofiable reference is returned to the caller. This is done
     * to not inflict the low level details about which #IPrettyMsg
     * implementation has been implemented in this store. The caller can work
     * with the returned #IPrettyMsg reference without being concerned about
     * these details.
     */
    virtual IMsg &appendMsg(const IMsg &msgToAppend) = 0;

    virtual IMsg &prependMsg(const IMsg &msgToAppend) = 0;
    /**
     * @brief Inserts the given message at index
     * 
     * \note If index is greater than the current size of the package, the
     * given message is appended to the current end of the package
     */
    virtual IMsg &insertMsg(const int index, const IMsg &msgToAppend) = 0;

    virtual void removeAt(const int index) = 0;
    virtual void removeMsgs(const int index, int count) = 0;

    virtual int size() const = 0;

    virtual const IMsg &at(const int index) const = 0;
    virtual IMsg &at(const int index) = 0;

    virtual void clear() = 0;

signals:
    void sgnl_msgAboutToBeInserted(
            const int index,
            const IMsg &msg
            );
    void sgnl_msgInserted(
            const int index,
            const IMsg &msg
            );

    void sgnl_msgAboutToBeRemoved(
            const int index,
            const int count
            );
    void sgnl_msgRemoved(
            const int index,
            const int count
            );

    void sgnl_AboutToBeCleared();
    void sgnl_Cleared();

    void sgnl_HasChanged();

public slots:
    virtual void slt_appendMsg(const IMsg &msgToAppend)
    {
        appendMsg(msgToAppend);
    }

    virtual void slt_prependMsg(const IMsg &msgToPrepend)
    {
        prependMsg(msgToPrepend);
    }

    virtual void slt_insertMsg(const int index, const IMsg &msgToInsert)
    {
        insertMsg(index,msgToInsert);
    }

    virtual void slt_removeMsgAt(const int index)
    {
        removeAt(index);
    }

    virtual void slt_removeMsgs(const int index, const int count)
    {
        removeMsgs(index,count);
    }
};

#endif /* ISENDMSGPACKAGESTORE_H */
