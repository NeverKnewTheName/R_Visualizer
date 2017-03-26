#ifndef MESSAGECONFIGWIDGET_H
#define MESSAGECONFIGWIDGET_H

#include <QWidget>

#include "IMessageConfig.h"

namespace Ui {
class MessageConfigWidget;
}

class MessageConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageConfigWidget(IMessageConfig *msgConfig, QWidget *parent = 0);
    ~MessageConfigWidget();

    void appendMappingWidget(QWidget *mappingWidgetToAppend);

private:
    Ui::MessageConfigWidget *ui;
    IMessageConfig *msgConfig;
};

#endif // MESSAGECONFIGWIDGET_H
