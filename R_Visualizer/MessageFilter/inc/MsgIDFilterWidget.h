#ifndef MSGIDFILTERWIDGET_H
#define MSGIDFILTERWIDGET_H

#include <QWidget>

namespace Ui {
class MsgIDFilterWidget;
}

class MsgIDFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgIDFilterWidget(QWidget *parent = 0);
    ~MsgIDFilterWidget();

private:
    Ui::MsgIDFilterWidget *ui;
};

#endif // MSGIDFILTERWIDGET_H
