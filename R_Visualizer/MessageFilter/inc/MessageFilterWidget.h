#ifndef MESSAGEFILTERWIDGET_H
#define MESSAGEFILTERWIDGET_H

#include <QWidget>

namespace Ui {
class MessageFilterWidget;
}

/**
 * @addtogroup MsgFilterGroup
 * 
 * @{
 */

class MessageFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageFilterWidget(QWidget *parent = 0);
    ~MessageFilterWidget();

    void addFilterWidget(QWidget *filterWidget);

private:
    Ui::MessageFilterWidget *ui;
};

/**
 * @}
 */

#endif // MESSAGEFILTERWIDGET_H
