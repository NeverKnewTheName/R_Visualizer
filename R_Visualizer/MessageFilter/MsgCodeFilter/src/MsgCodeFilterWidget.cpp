#include "MsgCodeFilterWidget.h"
#include "ui_msgcodefilterwidget.h"

MsgCodeFilterWidget::MsgCodeFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgCodeFilterWidget)
{
    ui->setupUi(this);
}

MsgCodeFilterWidget::~MsgCodeFilterWidget()
{
    delete ui;
}

void MsgCodeFilterWidget::addMsgCode(
        const MsgCodeType &msgCodeToAdd
        )
{
}

void MsgCodeFilterWidget::removeMsgCode(
        const MsgCodeType &msgCodeToRemove
        )
{
}

void MsgCodeFilterWidget::on_filterCodeLoadBtn_clicked()
{

}

void MsgCodeFilterWidget::on_filterCodeStoreBtn_clicked()
{

}

void MsgCodeFilterWidget::on_addFilterCodePushButton_clicked()
{

}

void MsgCodeFilterWidget::on_rmvFilterCodePushButton_clicked()
{

}

void MsgCodeFilterWidget::on_enableCodeFilterCheckBox_toggled(bool checked)
{

}

void MsgCodeFilterWidget::on_invertCodeFilterCheckBox_toggled(bool checked)
{

}

void MsgCodeFilterWidget::slt_addMsgCode(
        const MsgCodeType &msgCodeToAdd
        )
{
    addMsgCode(msgCodeToAdd);
}

void MsgCodeFilterWidget::slt_removeMsgCode(
        const MsgCodeType &msgCodeToRemove
        )
{
    removeMsgCode(msgCodeToRemove);
}
