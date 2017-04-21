#include "MsgCodeMappingWidget.h"
#include "ui_msgcodemappingwidget.h"

MsgCodeMappingWidget::MsgCodeMappingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgCodeMappingWidget)
{
    ui->setupUi(this);
}

MsgCodeMappingWidget::~MsgCodeMappingWidget()
{
    delete ui;
}

void MsgCodeMappingWidget::on_msgCodeStoreBtn_clicked()
{

}

void MsgCodeMappingWidget::on_msgCodeLoadBtn_clicked()
{

}

void MsgCodeMappingWidget::on_msgCodeRemoveBtn_clicked()
{

}

void MsgCodeMappingWidget::on_msgCodeAddBtn_clicked()
{

}
