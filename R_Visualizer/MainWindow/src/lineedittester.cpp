#include "lineedittester.h"
#include "ui_lineedittester.h"

LineEditTester::LineEditTester(
        MsgCodeLineEdit *lineEdit,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::LineEditTester),
    lineEdit(lineEdit)
{
    ui->setupUi(this);
}

LineEditTester::~LineEditTester()
{
    delete ui;
}

void LineEditTester::on_pushButton_clicked()
{
   ui->lineEdit->setText(static_cast<QString>(lineEdit->getMsgCode()));
}
