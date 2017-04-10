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
    explicit SendMsgPackageWidget(QWidget *parent = 0);
    ~SendMsgPackageWidget();

private:
    Ui::SendMsgPackageWidget *ui;
};

#endif // SENDMSGPACKAGEWIDGET_H
