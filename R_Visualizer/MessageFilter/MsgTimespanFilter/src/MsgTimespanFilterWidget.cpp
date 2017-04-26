#include "MsgTimespanFilterWidget.h"
#include "ui_msgtimespanfilterwidget.h"

#include "MsgTimespanFilter.h"

MsgTimespanFilterWidget::MsgTimespanFilterWidget(
        IMsgTimespanFilter *msgTimestampFilter,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgTimespanFilterWidget),
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

    ui->globalEnableTimestampFilterCheckBox->setChecked(
            msgTimestampFilter->isFilterEnabled()
            );

    connect(
            ui->enableTimestampToFilterCheckBox,
            &QCheckBox::toggled,
            msgTimestampFilter,
            &IMsgTimespanFilter::slt_enableTimestampTo
           );

    connect(
            ui->enableTimestampFromFilterCheckBox,
            &QCheckBox::toggled,
            msgTimestampFilter,
            &IMsgTimespanFilter::slt_enableTimestampFrom
           );

    connect(
            ui->invertTimestampFilterCheckBox,
            &QCheckBox::toggled,
            msgTimestampFilter,
            &IMsgTimespanFilter::slt_invertFilter
           );

    connect(
            ui->filterTimeStampToDateTimeEdit,
            &QDateTimeEdit::dateTimeChanged,
            msgTimestampFilter,
            &IMsgTimespanFilter::slt_changeTimestampTo
           );

    connect(
            ui->filterTimeStampFromDateTimeEdit,
            &QDateTimeEdit::dateTimeChanged,
            msgTimestampFilter,
            &IMsgTimespanFilter::slt_changeTimestampFrom
           );

    connect(
            ui->globalEnableTimestampFilterCheckBox,
            &QCheckBox::toggled,
            msgTimestampFilter,
            &IMsgTimespanFilter::slt_enableFilter
            );

    connect(
            msgTimestampFilter,
            &IMsgTimespanFilter::sgnl_TimestampFromChanged,
            ui->filterTimeStampFromDateTimeEdit,
            &QDateTimeEdit::setDateTime
           );

    connect(
            msgTimestampFilter,
            &IMsgTimespanFilter::sgnl_TimestampToChanged,
            ui->filterTimeStampToDateTimeEdit,
            &QDateTimeEdit::setDateTime
           );

}

MsgTimespanFilterWidget::~MsgTimespanFilterWidget()
{
    delete ui;
}

/* void MsgTimespanFilterWidget::on_filterTimeStampFromDateTimeEdit_dateTimeChanged(const QDateTime &dateTime) */
/* { */

/* } */

/* void MsgTimespanFilterWidget::on_filterTimeStampToDateTimeEdit_dateTimeChanged(const QDateTime &dateTime) */
/* { */

/* } */

/* void MsgTimespanFilterWidget::on_enableTimestampFromFilterCheckBox_toggled(bool checked) */
/* { */

/* } */

/* void MsgTimespanFilterWidget::on_enableTimestampToFilterCheckBox_toggled(bool checked) */
/* { */

/* } */

/* void MsgTimespanFilterWidget::on_invertTimestampFilterCheckBox_toggled(bool checked) */
/* { */

/* } */

/* void MsgTimespanFilterWidget::on_filterTimestampLoadBtn_clicked() */
/* { */

/* } */

/* void MsgTimespanFilterWidget::on_filterTimestampSaveBtn_clicked() */
/* { */

/* } */

/* void MsgTimespanFilterWidget::on_checkBox_toggled(bool checked) */
/* { */

/* } */
