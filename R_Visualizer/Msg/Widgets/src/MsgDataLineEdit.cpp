#include "MsgDataLineEdit.h"
#include "ui_msgdatalineedit.h"

MsgDataLineEdit::MsgDataLineEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgDataLineEdit)
{
    ui->setupUi(this);
}

MsgDataLineEdit::~MsgDataLineEdit()
{
    delete ui;
}

void MsgDataLineEdit::on_dataLineEdit_textChanged(const QString &arg1)
{

}

void MsgDataLineEdit::on_numFormatComboBox_currentIndexChanged(int index)
{

}
