#include "errlogview.h"
#include "ui_errlogview.h"
#include "errorlogentry.h"

#include <QDateTime>

#include <QDebug>

#include "fileparser.h"

ErrorLogView::ErrorLogView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorLogView)
{
    ui->setupUi(this);

    errLogModel = new ErrLogModel(this);

    ui->errLogTblV->setModel(errLogModel);
    QHeaderView *horzHeader = ui->errLogTblV->horizontalHeader();
    horzHeader->setSectionResizeMode(0, QHeaderView::Fixed);
    horzHeader->resizeSection(0, 150);
    horzHeader->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->errLogTblV->verticalHeader()->hide();

    ui->errLogTblV->setAlternatingRowColors(true);
    ui->errLogTblV->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->errLogTblV->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->errLogTblV->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
}

ErrorLogView::~ErrorLogView()
{
    delete ui;
}

void ErrorLogView::on_savePB_clicked()
{
    qDebug() << "ErrLogView" << "SAVE";
    qDebug() << "ADDING EXAMPLE ERROR";
    errLogModel->addErrEntry(new ErrorLogEntry(QDateTime::currentDateTime(), QString("This is some example error detail String!")));
}

void ErrorLogView::on_openPB_clicked()
{
    qDebug() << "ErrLogView" << "OPEN";
}

void ErrorLogView::on_closePB_clicked()
{
    qDebug() << "ErrLogView" << "CLOSE";
    emit close();
}

void ErrorLogView::on_addErrConfPB_clicked()
{
    qDebug() << "ErrLogConfig" << "ADD";
}

void ErrorLogView::on_removeErrConfPB_clicked()
{
    qDebug() << "ErrLogConfig" << "REMOVE";
}

void ErrorLogView::on_saveErrConfPB_clicked()
{
    qDebug() << "ErrLogConfig" << "SAVE";
}

void ErrorLogView::on_openErrConfPB_clicked()
{
    qDebug() << "ErrLogConfig" << "OPEN";
}

ErrLogModel *ErrorLogView::getErrLogModel() const
{
    return errLogModel;
}

void ErrorLogView::setErrLogModel(ErrLogModel *value)
{
    errLogModel = value;
}
