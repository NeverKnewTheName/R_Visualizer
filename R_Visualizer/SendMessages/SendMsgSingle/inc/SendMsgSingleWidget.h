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

class ISendMsgSingle;

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
