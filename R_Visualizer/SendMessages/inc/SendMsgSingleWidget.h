#ifndef SENDMSGSINGLEWIDGET_H
#define SENDMSGSINGLEWIDGET_H

#include <QWidget>

namespace Ui {
class SendMsgSingleWidget;
}

class SendMsgSingleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendMsgSingleWidget(QWidget *parent = 0);
    ~SendMsgSingleWidget();

private:
    Ui::SendMsgSingleWidget *ui;
};

#endif // SENDMSGSINGLEWIDGET_H
