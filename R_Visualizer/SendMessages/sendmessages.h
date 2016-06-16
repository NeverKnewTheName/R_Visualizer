#ifndef SENDMESSAGES_H
#define SENDMESSAGES_H

#include "can_packet.h"
#include "msgmodel.h"
#include "idmodel.h"
#include "msgtypemodel.h"
#include "userrolemngr.h"
#include <QWidget>

class MainWindow;

namespace Ui {
class SendMessages;
}

class SendMessages : public QWidget
{
    Q_OBJECT

public:
    explicit SendMessages(IDModel *idModel, MsgTypeModel *msgTypeModel, QWidget *parent = 0);
    ~SendMessages();

private:
    void initMsgPacketTableView();
    void emitSendMsg();

    qulonglong parseToNumber(QString numericalString);
    QString parseToString(qulonglong number);

    Ui::SendMessages *ui;
    friend class MainWindow;
    MsgModel *msgPcktModel;
    IDModel *idModel;
    MsgTypeModel *msgTypeModel;
    QStringList inputMasks;

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
};

#endif // SENDMESSAGES_H
