#ifndef SENDMSGPACKAGESTORENOTIFIER_H
#define SENDMSGPACKAGESTORENOTIFIER_H

#include <QObject>

class ISendMsgPackageStore;

class SendMsgPackageStoreNotifier : public QObject
{
    Q_OBJECT
public:
    SendMsgPackageStoreNotifier(
            ISendMsgPackageStore *msgPackageStore
            QObject *parent = Q_NULLPTR
            );
    virtual ~SendMsgPackageStoreNotifier();

    virtual void emitSgnlMsgAboutToBeAppended();
    virtual void emitSgnlMsgAppended();

    virtual void emitSgnlMsgAboutToBePrepended();
    virtual void emitSgnlMsgPrepended();

    virtual void emitSgnlMsgAboutToBeInserted(const int index);
    virtual void emitSgnlMsgInserted();

    virtual void emitSgnlMsgAboutToBeRemoved(const int index);
    virtual void emitSgnlMsgRemoved();

signals:
    void sgnl_MsgAboutToBeAppended();
    void sgnl_MsgAppended();

    void sgnl_MsgAboutToBePrepended();
    void sgnl_MsgPrepended();

    void sgnl_MsgAboutToBeInserted(const int index);
    void sgnl_MsgInserted();

    void sgnl_MsgAboutToBeRemoved(const int index);
    void sgnl_MsgRemoved();

public slots:
    void slt_appendMsg(const IPrettyMsg &mappingToAdd);
    void slt_prependMsg(const IPrettyMsg &mappingToAdd);
    void slt_insertMsg(const int index, const IPrettyMsg &mappingToAdd);
    void slt_removeMsg(const int index);

private:
    ISendMsgPackageStore *msgPackageStore;
};

#endif /* SENDMSGPACKAGESTORENOTIFIER_H */
