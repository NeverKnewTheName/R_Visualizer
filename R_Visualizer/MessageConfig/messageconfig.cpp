#include "messageconfig.h"
#include "ui_messageconfig.h"

MessageConfig::MessageConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageConfig)
{
    ui->setupUi(this);
}

MessageConfig::~MessageConfig()
{
    delete ui;
}
