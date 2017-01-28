#ifndef SENDMESSAGES_H
#define SENDMESSAGES_H

#include "msg.h"
#include "can_packet.h"
#include "msgmodel.h"
#include "idmodel.h"
#include "msgtypemodel.h"
#include "userrolemngr.h"
#include <QWidget>
#include <QCompleter>

class MainWindow;

namespace Ui {
class SendMessages;
}

class SendMessages : public QWidget
{
    Q_OBJECT

public:
    explicit SendMessages(IDModel &idModel, MsgTypeModel &msgTypeModel, QWidget *parent = 0);
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
    MsgModel msgPcktModel; //MAYBE REFERENCE???
    IDModel &idModel;
    MsgTypeModel &msgTypeModel;
    QStringList inputMasks;
    QCompleter idCompleter;
    QCompleter codeCompleter;

    int currentDataFormatIndex;

signals:
    void sigSendCANPacket(CAN_PacketPtr);

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
};

#endif // SENDMESSAGES_H
