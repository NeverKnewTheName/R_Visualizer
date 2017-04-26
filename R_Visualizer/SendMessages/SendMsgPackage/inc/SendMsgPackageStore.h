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
#include "PrettyMsg.h"

/**
 * @brief The SendMsgPackageStore
 */
class SendMsgPackageStore : public QObject, public ISendMsgPackageStore
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
    virtual IPrettyMsg &appendMsg(const IPrettyMsg &msgToAppend = PrettyMsg<Msg>());

    virtual IPrettyMsg &appendMsg(const IMsg &msgToAppend);

    virtual IPrettyMsg &prependMsg(const IPrettyMsg &msgToAppend = PrettyMsg<Msg>());
    virtual IPrettyMsg &prependMsg(const IMsg &msgToAppend);
    /**
     * @brief Inserts the given message at index
     * 
     * \note If index is greater than the current size of the package, the
     * given message is appended to the current end of the package
     */
    virtual IPrettyMsg &insertMsg(
            const int index,
            const IPrettyMsg &msgToAppend = PrettyMsg<Msg>()
            );

    virtual IPrettyMsg &insertMsg(
            const int index,
            const IMsg &msgToAppend
            );

    virtual void removeMsgFirstMatch(const IPrettyMsg &msgToRemove);

    virtual void removeMsgLastMatch(const IPrettyMsg &msgToRemove);

    virtual void removeMsgsAllMatches(const IPrettyMsg &msgToRemove);

signals:
    void sgnl_msgAboutToBeAppended();
    void sgnl_msgAppended();

    void sgnl_msgAboutToBePrepended();
    void sgnl_msgPrepended();

    void sgnl_msgAboutToBeInserted(const int index);
    void sgnl_msgInserted();

    void sgnl_msgAboutToBeRemoved();
    void sgnl_msgRemoved();

public slots:
    void slt_appendMsg(const IPrettyMsg &msgToAppend);
    void slt_prependMsg(const IPrettyMsg &msgToPrepend);
    void slt_insertMsg(const int index, const IPrettyMsg &msgToInsert);
    void slt_removeMsgFirstMatch(const IPrettyMsg &msgToRemove);
    void slt_removeMsgLastMatch(const IPrettyMsg &msgToRemove);
    void slt_removeMsgsAllMatches(const IPrettyMsg &msgToRemove);

private:
    QVector<PrettyMsg<Msg>> msgStorage;
};

#endif /* SENDMSGPACKAGESTORE_H */
