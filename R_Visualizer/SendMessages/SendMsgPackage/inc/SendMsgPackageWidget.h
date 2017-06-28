/**
 * @file SendMsgPackageWidget.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The SendMsgPackageWidget sub-module
 */
#ifndef SENDMSGPACKAGEWIDGET_H
#define SENDMSGPACKAGEWIDGET_H

#include <QWidget>

#include "SendMsgPackageModel.h"

class ISendMsgPackage;

class IMsgIDMappingManager;
class IMsgCodeMappingManager;
class IMsgDataMappingManager;

namespace Ui {
class SendMsgPackageWidget;
}

/**
 * @brief THe SendMsgPackageWidget
 */
class SendMsgPackageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendMsgPackageWidget(
            ISendMsgPackage *sendMsgPackage,
            QWidget *parent = Q_NULLPTR
            );
    ~SendMsgPackageWidget();

    void setMsgIDMappingManager(IMsgIDMappingManager *msgIDMappingManager);
    void setMsgCodeMappingManager(IMsgCodeMappingManager *msgCodeMappingManager);
    void setMsgDataMappingManager(IMsgDataMappingManager *msgDataMappingManager);

private slots:
    void on_sndPcktAddBtn_clicked();
    void on_sndPcktRmvBtn_clicked();
    void on_sndPcktLoadBtn_clicked();
    void on_sndPcktStoreBtn_clicked();
    void on_sndPcktSendBtn_clicked();
    void on_sndPcktClrBtn_clicked();
    void on_pushButton_clicked();
    void on_sendDelaySpinBox_valueChanged(int arg1);

private:
    void init();

private:
    Ui::SendMsgPackageWidget *ui;
    ISendMsgPackage *sendMsgPackage;
    SendMsgPackageModel sendMsgPackageModel;
    IMsgIDMappingManager *msgIDMappingManager;
    IMsgCodeMappingManager *msgCodeMappingManager;
    IMsgDataMappingManager *msgDataMappingManager;
};

#endif // SENDMSGPACKAGEWIDGET_H
