/**
 * @file sendmessages.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief The Send Messages Module
 */
#ifndef SENDMESSAGES_H
#define SENDMESSAGES_H

#include <QWidget>
#include <QCompleter>

class MainWindow;
class MessageConfig;
class FileParser;

#include "msg.h"
#include "can_packet.h"
#include "sendmsgmodel.h"
#include "userrolemngr.h"
#include "IFileParsable.h"

namespace Ui {
class SendMessages;
}

/**
 * @brief The SendMessages
 */
class SendMessages : public QWidget, public IFileParsable
{
    Q_OBJECT

public:
    explicit SendMessages(
            const MessageConfig *msgConfig,
            QWidget *parent = 0);
    ~SendMessages();

    void accept(FileParser *visitor);
    void updateMsgPacketModel();
    void setMsgPacketModel(const SendMsgModel &newMsgPacketModel);

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
    QStringList inputMasks;
    const MessageConfig *msgConfig;

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

    void slt_appendMsgToMsgPacket(const Msg &msg);

    void slt_IDRepAdded(const IDRep &addedIDRep);
    void slt_IDRepUpdated(const IDRep &updatedIDRep);
    void slt_IDRepRemoved(const MsgIDType relatedID);
    void slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep);
    void slt_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep);
    void slt_MsgTypeRepRemoved(const MsgCodeType relatedCode);
    /* void slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep); */
    /* void slt_MsgDataRepUpdated(const MsgDataRep &changedMsgDataRep); */
    /* void slt_MsgDataRepRemoved(const MsgCodeType codeWhoseDataRepWasRemoved); */
};

#endif // SENDMESSAGES_H
