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

class IMessageStream;
class MsgStreamModel;

namespace Ui {
class MessageStreamWidget;
}

/**
 * @addtogroup MessageStreamGroup
 *
 * @{
 */

/**
 * @brief The MessageStreamWidget
 */
class MessageStreamWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageStreamWidget(
            IMessageStream *msgStream,
            MsgStreamModel *msgStreamModel,
            QWidget *parent = Q_NULLPTR
            );
    ~MessageStreamWidget();

private slots:
    void on_loadBtn_clicked();

    void on_storeBtn_clicked();

    void on_scrollTopBtn_clicked();

    void on_scrollBottomBtn_clicked();

    void on_followUpCheckBox_toggled(bool checked);

    void on_clearStreamBtn_clicked();

private:
    void init();
    void connectToMessageStream();

private:
    Ui::MessageStreamWidget *ui;
    IMessageStream *msgStream;
    MsgStreamModel *msgStreamModel;
};

/**
 * @}
 */
#endif // MESSAGESTREAMWIDGET_H
