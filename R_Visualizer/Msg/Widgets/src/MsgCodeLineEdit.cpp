#include "MsgCodeLineEdit.h"
#include "ui_msgcodelineedit.h"

MsgCodeLineEdit::MsgCodeLineEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgCodeLineEdit)
{
    ui->setupUi(this);
}

MsgCodeLineEdit::~MsgCodeLineEdit()
{
    delete ui;
}

void MsgCodeLineEdit::on_codeLineEdit_textChanged(const QString &arg1)
{

}

void MsgCodeLineEdit::on_numFormatComboBox_currentIndexChanged(int index)
{

}
