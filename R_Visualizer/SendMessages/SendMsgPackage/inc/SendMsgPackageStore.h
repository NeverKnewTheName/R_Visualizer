/**
 * @file SendMsgPackageStore.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The default implementation for the #ISendMsgPackageStore
 */
#ifndef SENDMSGPACKAGESTORE_H
#define SENDMSGPACKAGESTORE_H

#include <QObject>
#include <QVector>

#include "ISendMsgPackageStore.h"
#include "IMsg.h"
#include "Msg.h"

/**
 * @brief The SendMsgPackageStore
 */
class SendMsgPackageStore : public ISendMsgPackageStore
{
    Q_OBJECT
public:
    SendMsgPackageStore(
            QObject *parent = Q_NULLPTR
            );
    virtual ~SendMsgPackageStore();

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
    virtual IMsg &appendMsg(const IMsg &msgToAppend = Msg());

    virtual IMsg &prependMsg(const IMsg &msgToAppend = Msg());
    /**
     * @brief Inserts the given message at index
     * 
     * \note If index is greater than the current size of the package, the
     * given message is appended to the current end of the package
     */
    virtual IMsg &insertMsg(
            const int index,
            const IMsg &msgToAppend = Msg()
            );

    virtual void removeAt(const int index);
    virtual void removeMsgs(const int index, int count);

    virtual int size() const;

    virtual const IMsg &at(const int index) const;
    virtual IMsg &at(const int index);

    virtual void clear();

private:
    QVector<Msg> msgStorage;

    // IFileParsable interface
public:
    virtual void accept(FileParser *visitor);
};

#endif /* SENDMSGPACKAGESTORE_H */
