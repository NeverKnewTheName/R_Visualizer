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
    virtual ~MsgIDFilterWidget();

    void addMsgID(const MsgIDType &msgIDToAdd);
    void removeMsgID(const MsgIDType &msgIDToRemove);

signals:
    sgnl_MsgIDAdded(const MsgIDType &addedMsgID);
    sgnl_MsgIDRemoved(const MsgIDType &removedMsgID);

    sgnl_filterEnabled(const bool enable);
    sgnl_filterInverted(const bool invert);

public slots:
    slt_addMsgID(const MsgIDType &msgIDToAdd);
    slt_removeMsgID(const MsgIDType &msgIDToRemove);

private slots:
    void on_addFilterIDPushButton_clicked();

    void on_rmvFilterIDPushButton_clicked();

    void on_filterIDSaveBtn_clicked();

    void on_filterIDLoadBtn_clicked();

    void on_enableIDFilterCheckBox_toggled(bool checked);

    void on_checkBox_toggled(bool checked);

private:
    Ui::MsgIDFilterWidget *ui;
};

#endif // MSGIDFILTERWIDGET_H
