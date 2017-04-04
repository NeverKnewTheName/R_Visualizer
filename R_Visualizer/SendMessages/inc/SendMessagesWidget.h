#ifndef SENDMESSAGESWIDGET_H
#define SENDMESSAGESWIDGET_H

#include <QWidget>

namespace Ui {
class SendMessagesWidget;
}

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
