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
    explicit SendMessagesWidget(QWidget *parent = 0);
    ~SendMessagesWidget();

private:
    Ui::SendMessagesWidget *ui;
};

#endif // SENDMESSAGESWIDGET_H
