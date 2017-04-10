/**
 * @file MessageStreamWidget.h
 * @author Christian Neuberger
 * @date 2017-04-11
 *
 * @brief The default widget for the MessageStream
 */
#ifndef MESSAGESTREAMWIDGET_H
#define MESSAGESTREAMWIDGET_H

#include <QWidget>

namespace Ui {
class MessageStreamWidget;
}

/**
 * @brief The MessageStreamWidget
 */
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
