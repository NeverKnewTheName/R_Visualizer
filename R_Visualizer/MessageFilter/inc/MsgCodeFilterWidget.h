#ifndef MSGCODEFILTERWIDGET_H
#define MSGCODEFILTERWIDGET_H

#include <QWidget>

namespace Ui {
class MsgCodeFilterWidget;
}

class MsgCodeFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgCodeFilterWidget(QWidget *parent = 0);
    ~MsgCodeFilterWidget();

private:
    Ui::MsgCodeFilterWidget *ui;
};

#endif // MSGCODEFILTERWIDGET_H
