#ifndef SENDMSGPACKAGEWIDGET_H
#define SENDMSGPACKAGEWIDGET_H

#include <QWidget>

namespace Ui {
class SendMsgPackageWidget;
}

class SendMsgPackageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendMsgPackageWidget(QWidget *parent = 0);
    ~SendMsgPackageWidget();

private:
    Ui::SendMsgPackageWidget *ui;
};

#endif // SENDMSGPACKAGEWIDGET_H
