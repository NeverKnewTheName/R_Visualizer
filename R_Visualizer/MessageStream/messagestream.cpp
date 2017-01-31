#include "messagestream.h"
#include "ui_messagestream.h"

MessageStream::MessageStream(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageStream)
{
    ui->setupUi(this);
}

MessageStream::~MessageStream()
{
    delete ui;
}
