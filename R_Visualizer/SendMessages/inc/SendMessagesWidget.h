/**
 * @file SendMessagesWidget.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The default implementation of the SendMessages widget
 */
#ifndef SENDMESSAGESWIDGET_H
#define SENDMESSAGESWIDGET_H

#include <QWidget>

class ISendMessages;

namespace Ui {
class SendMessagesWidget;
}

/**
 * @brief The SendMessagesWidget
 */
class SendMessagesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendMessagesWidget(
            ISendMessages *sendMessages,
            QWidget *parent = Q_NULLPTR
            );
    ~SendMessagesWidget();

    void addSendMsgSingleWidget(QWidget *sendMsgWidget);

private:
    void connectSendMessages();

private:
    Ui::SendMessagesWidget *ui;
    ISendMessages *sendMessages;
};

#endif // SENDMESSAGESWIDGET_H
