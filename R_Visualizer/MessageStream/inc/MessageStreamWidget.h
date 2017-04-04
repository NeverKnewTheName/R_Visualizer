#ifndef MESSAGESTREAMWIDGET_H
#define MESSAGESTREAMWIDGET_H

#include <QWidget>

namespace Ui {
class MessageStreamWidget;
}

class MessageStreamWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageStreamWidget(QWidget *parent = 0);
    ~MessageStreamWidget();

private:
    Ui::MessageStreamWidget *ui;
};

#endif // MESSAGESTREAMWIDGET_H
