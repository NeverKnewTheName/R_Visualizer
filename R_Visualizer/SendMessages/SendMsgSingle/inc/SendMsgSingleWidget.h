/**
 * @file SendMsgSingleWidget.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The SendMsgSingleWidget
 */
#ifndef SENDMSGSINGLEWIDGET_H
#define SENDMSGSINGLEWIDGET_H

#include <QWidget>
#include <QCompleter>

class ISendMsgSingle;
class IMsgIDMappingManager;
class IMsgCodeMappingManager;
class IMsgDataMappingManager;
class IMsg;

namespace Ui {
class SendMsgSingleWidget;
}

/**
 * @addtogroup SendMessagesSingleGroup
 * 
 * @{
 */

/**
 * @brief The SendMsgSingleWidget
 */
class SendMsgSingleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendMsgSingleWidget(
            ISendMsgSingle *sendMsgSingle,
            QWidget *parent = 0
            );
    ~SendMsgSingleWidget();

    void setMsgIDMapping(IMsgIDMappingManager *msgIDMappingManager);
    void setMsgIDCompleter(QCompleter *msgIDCompleter);
    void setMsgCodeMapping(IMsgCodeMappingManager *msgCodeMappingManager);
    void setMsgCodeCompleter(QCompleter *msgCodeCompleter);
    void setMsgDataMapping(IMsgDataMappingManager *msgDataMappingManager);

signals:
    void sgnl_AddToPackage(const IMsg &msgToAdd);

private slots:
    void on_sndMsgSendBtn_clicked();

    void on_sndMsgAddToPackageBtn_clicked();

    void on_openMsgBtn_clicked();

    void on_saveMsgBtn_clicked();

private:
    void connectSendMsgSingle();

private:
    Ui::SendMsgSingleWidget *ui;
    ISendMsgSingle *sendMsgSingle;
};

/**
 * @}
 */

#endif // SENDMSGSINGLEWIDGET_H
