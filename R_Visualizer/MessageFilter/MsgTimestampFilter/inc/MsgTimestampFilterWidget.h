#ifndef MSGTIMESTAMPFILTERWIDGET_H
#define MSGTIMESTAMPFILTERWIDGET_H

#include <QWidget>

#include <QDateTime>

class MsgTimestampFilter;

namespace Ui {
class MsgTimestampFilterWidget;
}

class MsgTimestampFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgTimestampFilterWidget(
            MsgTimestampFilter *msgTimestampFilter,
            QWidget *parent = Q_NULLPTR
            );
    ~MsgTimestampFilterWidget();

private slots:
    void on_filterTimeStampFromDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_filterTimeStampToDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_enableTimestampFromFilterCheckBox_toggled(bool checked);

    void on_enableTimestampToFilterCheckBox_toggled(bool checked);

    void on_invertTimestampFilterCheckBox_toggled(bool checked);

    void on_filterTimestampLoadBtn_clicked();

    void on_filterTimestampSaveBtn_clicked();

    void on_checkBox_toggled(bool checked);

private:
    Ui::MsgTimestampFilterWidget *ui;
    MsgTimestampFilter *msgTimestampFilter;
};

#endif // MSGTIMESTAMPFILTERWIDGET_H
