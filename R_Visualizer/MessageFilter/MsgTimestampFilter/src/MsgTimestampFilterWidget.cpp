#include "MsgTimestampFilterWidget.h"
#include "ui_msgtimestampfilterwidget.h"

#include "MsgTimestampFilter.h"

MsgTimestampFilterWidget::MsgTimestampFilterWidget(
        MsgTimestampFilter *msgTimestampFilter,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgTimestampFilterWidget),
    msgTimestampFilter(msgTimestampFilter)
{
    ui->setupUi(this);

    //ToDO Fill widget with values from the filter!
    
    ui->filterTimeStampFromDateTimeEdit->setDateTime(
            msgTimestampFilter->getTimestampFrom()
        );

    ui->filterTimeStampToDateTimeEdit->setDateTime(
            msgTimestampFilter->getTimestampTo()
        );

    ui->enableTimestampFromFilterCheckBox->setChecked(
            msgTimestampFilter->isTimestampFilterFromEnabled()
            );

    ui->enableTimestampToFilterCheckBox->setChecked(
            msgTimestampFilter->isTimestampFilterToEnabled()
            );

    ui->invertTimestampFilterCheckBox->setChecked(
            msgTimestampFilter->isFilterInverted()
            );

    connect(
            ui->enableTimestampToFilterCheckBox,
            &QCheckBox::toggled,
            msgTimestampFilter,
            &MsgTimestampFilter::slt_enableTimestampTo
           );

    connect(
            ui->enableTimestampFromFilterCheckBox,
            &QCheckBox::toggled,
            msgTimestampFilter,
            &MsgTimestampFilter::slt_enableTimestampFrom
           );

    connect(
            ui->invertTimestampFilterCheckBox,
            &QCheckBox::toggled,
            msgTimestampFilter,
            &MsgTimestampFilter::slt_invertFilter
           );

    connect(
            ui->filterTimeStampToDateTimeEdit,
            &QDateTimeEdit::dateTimeChanged,
            msgTimestampFilter,
            &MsgTimestampFilter::slt_changeTimestampTo
           );

    connect(
            ui->filterTimeStampFromDateTimeEdit,
            &QDateTimeEdit::dateTimeChanged,
            msgTimestampFilter,
            &MsgTimestampFilter::slt_changeTimestampFrom
           );

    connect(
            msgTimestampFilter,
            &MsgTimestampFilter::sgnl_TimestampFromChanged,
            ui->filterTimeStampFromDateTimeEdit,
            &QDateTimeEdit::setDateTime
           );

    connect(
            msgTimestampFilter,
            &MsgTimestampFilter::sgnl_TimestampToChanged,
            ui->filterTimeStampToDateTimeEdit,
            &QDateTimeEdit::setDateTime
           );

}

MsgTimestampFilterWidget::~MsgTimestampFilterWidget()
{
    delete ui;
}

void MsgTimestampFilterWidget::on_filterTimeStampFromDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{

}

void MsgTimestampFilterWidget::on_filterTimeStampToDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{

}

void MsgTimestampFilterWidget::on_enableTimestampFromFilterCheckBox_toggled(bool checked)
{

}

void MsgTimestampFilterWidget::on_enableTimestampToFilterCheckBox_toggled(bool checked)
{

}

void MsgTimestampFilterWidget::on_invertTimestampFilterCheckBox_toggled(bool checked)
{

}

void MsgTimestampFilterWidget::on_filterTimestampLoadBtn_clicked()
{

}

void MsgTimestampFilterWidget::on_filterTimestampSaveBtn_clicked()
{

}
