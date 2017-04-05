#include "MsgIDFilterWidget.h"
#include "ui_msgidfilterwidget.h"

MsgIDFilterWidget::MsgIDFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgIDFilterWidget)
{
    ui->setupUi(this);
}

MsgIDFilterWidget::~MsgIDFilterWidget()
{
    delete ui;
}

void MsgIDFilterWidget::on_addFilterIDPushButton_clicked()
{

}

void MsgIDFilterWidget::on_rmvFilterIDPushButton_clicked()
{

}

void MsgIDFilterWidget::on_filterIDSaveBtn_clicked()
{

}

void MsgIDFilterWidget::on_filterIDLoadBtn_clicked()
{

}

void MsgIDFilterWidget::on_enableIDFilterCheckBox_toggled(bool checked)
{

}

void MsgIDFilterWidget::on_checkBox_toggled(bool checked)
{

}
