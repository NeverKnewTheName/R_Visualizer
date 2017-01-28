#include "msgdatawidget.h"
#include "ui_msgdatawidget.h"

MsgDataWidget::MsgDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgDataWidget),
    DataShown(false)
{
    ui->setupUi(this);
    ui->DataTextEdit->hide();
}

MsgDataWidget::MsgDataWidget(const MsgDataWidget &other) :
    QWidget(other.parentWidget()),
    ui(new Ui::MsgDataWidget),
    DataShown(other.getDataShown())
{

}

MsgDataWidget::~MsgDataWidget()
{
    delete ui;
}

void MsgDataWidget::setCode(const QString &code)
{
    ui->CodeLabel->setText(code);
}

void MsgDataWidget::setData(const QString &Data)
{
    ui->DataTextEdit->setText(Data);
}

void MsgDataWidget::on_ShowDataPushButton_clicked()
{
    DataShown = !DataShown;
    if(DataShown)
    {
        ui->DataTextEdit->show();
    }
    else
    {
        ui->DataTextEdit->hide();
    }
}

bool MsgDataWidget::getDataShown() const
{
    return DataShown;
}
