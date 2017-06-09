/**
 * @file ISendMsgPackage.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The interface for sending message packages
 */
#ifndef ISENDMSGPACKAGE_H
#define ISENDMSGPACKAGE_H

#include <QObject>

class IMsg;
class Msg;

class ISendMsgPackageStore;

/**
 * @brief The ISendMsgPackage interface
 */
class ISendMsgPackage : public QObject
{
    Q_OBJECT
public:
    ISendMsgPackage(QObject *parent = Q_NULLPTR) : QObject(parent){}
    virtual ~ISendMsgPackage(){}

    virtual void appendMsg(const IMsg &msgToAppend) = 0;
    virtual void prependMsg(const IMsg &msgToAppend) = 0;
    /**
     * @brief Inserts the given message at index
     * 
     * \note If index is greater than the current size of the package, the
     * given message is appended to the current end of the package
     */
    virtual void insertMsg(const int index, const IMsg &msgToAppend) = 0;

    virtual void removeAt(const int index) = 0;
    virtual void removeMsgs(const int index, int count) = 0;

    virtual void sendMessages() = 0;

    virtual ISendMsgPackageStore *getStore() const = 0;

    virtual int getSendDelay() const = 0;
    virtual void setSendDelay(const int sendDelay) = 0;

signals:
    void sgnl_sendMsg(const IMsg &msgToSend);
    void sgnl_SendStdMsg(const Msg &msg);
    void sgnl_msgAppended();
    void sgnl_msgPrepended();
    void sgnl_msgRemoved();

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

    virtual void slt_removeAt(const int index)
    {
        removeAt(index);
    }

    virtual void slt_removeMsgs(const int index, int count)
    {
        removeMsgs(index,count);
    }
};

#endif /* ISENDMSGPACKAGE_H */
