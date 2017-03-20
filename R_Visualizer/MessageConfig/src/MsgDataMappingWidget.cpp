#include "MsgDataMappingWidget.h"
#include "ui_msgdatamappingwidget.h"

MsgDataMappingWidget::MsgDataMappingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgDataMappingWidget)
{
    ui->setupUi(this);
}

MsgDataMappingWidget::~MsgDataMappingWidget()
{
    delete ui;
}

void MsgDataMappingWidget::on_msgDataStoreBtn_clicked()
{

}

void MsgDataMappingWidget::on_msgDataLoadBtn_clicked()
{

}

void MsgDataMappingWidget::on_msgDataRemoveBtn_clicked()
{

}

void MsgDataMappingWidget::on_msgDataAddBtn_clicked()
{

}
