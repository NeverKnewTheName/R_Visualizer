#ifndef MSGTIMESTAMPFILTERWIDGET_H
#define MSGTIMESTAMPFILTERWIDGET_H

#include <QWidget>

namespace Ui {
class MsgTimestampFilterWidget;
}

class MsgTimestampFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgTimestampFilterWidget(QWidget *parent = 0);
    ~MsgTimestampFilterWidget();

private:
    Ui::MsgTimestampFilterWidget *ui;
};

#endif // MSGTIMESTAMPFILTERWIDGET_H
