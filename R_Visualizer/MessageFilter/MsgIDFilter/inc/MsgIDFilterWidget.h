/**
 * @file MsgIDFilterWidget.h
 * @author Christian Neuberger
 * @date 2017-04-24
 * 
 * @brief The Widget for the message id filter
 */
#ifndef MSGIDFILTERWIDGET_H
#define MSGIDFILTERWIDGET_H

#include <QWidget>
#include <QAbstractItemDelegate>

#include "MsgIDType.h"

class MsgIDFilter;
class MsgIDFilterModel;
class IMsgIDMappingManager;

namespace Ui {
class MsgIDFilterWidget;
}

/**
 * @addtogroup MsgIDFilterGroup
 * 
 * @{
 */

/**
 * @brief The MsgIDFilterWidget
 */
class MsgIDFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgIDFilterWidget(
            MsgIDFilter *msgIDFilter,
            MsgIDFilterModel *msgIDFilterModel,
            QWidget *parent = Q_NULLPTR
            );
    virtual ~MsgIDFilterWidget();

    void addMsgID(const MsgIDType &msgIDToAdd);
    void removeMsgID(const MsgIDType &msgIDToRemove);

    void setMsgIDMappingManager(IMsgIDMappingManager *msgIDMappingManager);
    void setDelegate(QAbstractItemDelegate *delegate);

signals:
    void sgnl_MsgIDAdded(const MsgIDType &addedMsgID);
    void sgnl_MsgIDRemoved(const MsgIDType &removedMsgID);

    void sgnl_filterEnabled(const bool enable);
    void sgnl_filterInverted(const bool invert);

public slots:
    void slt_addMsgID(const MsgIDType &msgIDToAdd);
    void slt_removeMsgID(const MsgIDType &msgIDToRemove);

private slots:
    void on_addFilterIDPushButton_clicked();
    void on_rmvFilterIDPushButton_clicked();
    void on_filterIDSaveBtn_clicked();
    void on_filterIDLoadBtn_clicked();

    /* void on_enableIDFilterCheckBox_toggled(bool checked); */

    /* void on_checkBox_toggled(bool checked); */

private:
    void init();

private:
    Ui::MsgIDFilterWidget *ui;
    MsgIDFilter *msgIDFilter;
    MsgIDFilterModel *msgIDFilterModel;
    IMsgIDMappingManager *msgIDMappingManager;
};

/**
 * @}
 */

#endif // MSGIDFILTERWIDGET_H
