#ifndef SENDMESSAGES_H
#define SENDMESSAGES_H

#include <QWidget>
#include <QCompleter>

class MainWindow;
class IDModel;
class MsgTypeModel;

#include "msg.h"
#include "can_packet.h"
#include "sendmsgmodel.h"
#include "userrolemngr.h"

namespace Ui {
class SendMessages;
}

class SendMessages : public QWidget
{
    Q_OBJECT

public:
    explicit SendMessages(const IDModel &idModel, const MsgTypeModel &msgTypeModel, QWidget *parent = 0);
    ~SendMessages();

private:
    void convertMsgData(QString &msgDataString, int oldIndex, int newIndex);
    void initMsgPacketTableView();
    void emitSendMsg();

    DataByteVect extractMsgData(QString msgDataString, int formatIndex);
    QString createMsgData(DataByteVect msgDataBytes, int formatIndex);

    qulonglong parseToNumber(QString numericalString);
    QString parseToString(qulonglong number);

    Ui::SendMessages *ui;
    friend class MainWindow;
    SendMsgModel msgPcktModel; //MAYBE REFERENCE???
    const IDModel &idModel;
    const MsgTypeModel &msgTypeModel;
    QStringList inputMasks;

    int currentDataFormatIndex;

signals:
    void sigSendCANPacket(CAN_PacketPtr);
    void sgnl_SendMsg(const Msg &msgToSend);

private slots:
    void applyRole(UserRoleMngr::UserRole roleToSwitchTo);
    void on_sndPcktLoadBtn_clicked();
    void on_sndPcktStoreBtn_clicked();
    void on_sndMsgSendBtn_clicked();
    void on_sndPcktSendBtn_clicked();

    void idChanged(const QString &newIDName);
    void codeChanged(const QString &newCodeName);
    void on_msgDataFormatComboBox_currentIndexChanged(int index);
    void on_sndPcktClrBtn_clicked();
    void on_sndMsgAddToPacketBtn_clicked();
    void on_sndMsgMsgLineEdit_returnPressed();
    void on_sndPcktRmvBtn_clicked();

    void slt_IDRepAdded(const IDRep &addedIDRep);
    void slt_IDRepUpdated(const IDRep &changedIDRep);
    void slt_IDRepRemoved(const MsgIDType idWhoseIDRepWasRemoved);
    void slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep);
    void slt_MsgTypeRepUpdated(const MsgTypeRep &changedMsgTypeRep);
    void slt_MsgTypeRepRemoved(const MsgCodeType codeWhoseMsgTypeRepWasRemoved);
    /* void slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep); */
    /* void slt_MsgDataRepUpdated(const MsgDataRep &changedMsgDataRep); */
    /* void slt_MsgDataRepRemoved(const MsgCodeType codeWhoseDataRepWasRemoved); */
};

#endif // SENDMESSAGES_H
