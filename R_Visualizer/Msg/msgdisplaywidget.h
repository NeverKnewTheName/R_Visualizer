#ifndef MSGDISPLAYWIDGET_H
#define MSGDISPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class MsgDisplayWidget;
}

class MsgDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgDisplayWidget(QWidget *parent = 0);
    ~MsgDisplayWidget();


private:
    Ui::MsgDisplayWidget *ui;
};

#endif // MSGDISPLAYWIDGET_H
