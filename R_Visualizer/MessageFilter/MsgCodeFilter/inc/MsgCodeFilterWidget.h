/**
 * @file MsgCodeFilterWidget.h
 * @author Christian Neuberger
 * @date 2017-04-24
 * 
 * @brief The Widget for the message code filter
 */
#ifndef MSGCODEFILTERWIDGET_H
#define MSGCODEFILTERWIDGET_H

#include <QWidget>

#include "MsgCodeType.h"

class MsgCodeFilter;
class MsgCodeFilterModel;

namespace Ui {
class MsgCodeFilterWidget;
}

/**
 * @addtogroup MsgCodeFilterGroup
 * 
 * @{
 */

/**
 * @brief The MsgCodeFilterWidget
 */
class MsgCodeFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgCodeFilterWidget(
            MsgCodeFilter *msgCodeFilter,
            MsgCodeFilterModel *msgCodeFilterModel,
            QWidget *parent = Q_NULLPTR
            );
    virtual ~MsgCodeFilterWidget();

    void addMsgCode(const MsgCodeType &msgCodeToAdd);
    void removeMsgCode(const MsgCodeType &msgCodeToRemove);

signals:
    void sgnl_MsgCodeAdded(const MsgCodeType &addedMsgCode);
    void sgnl_MsgCodeRemoved(const MsgCodeType &removedMsgCode);

    void sgnl_filterEnabled(const bool enable);
    void sgnl_filterInverted(const bool invert);

public slots:
    void slt_addMsgCode(const MsgCodeType &msgCodeToAdd);
    void slt_removeMsgCode(const MsgCodeType &msgCodeToRemove);

private slots:
    void on_filterCodeLoadBtn_clicked();

    void on_filterCodeStoreBtn_clicked();

    void on_addFilterCodePushButton_clicked();

    void on_rmvFilterCodePushButton_clicked();

    /* void on_enableCodeFilterCheckBox_toggled(bool checked); */

    /* void on_invertCodeFilterCheckBox_toggled(bool checked); */

private:
    void init();

private:
    Ui::MsgCodeFilterWidget *ui;
    MsgCodeFilter *msgCodeFilter;
    MsgCodeFilterModel *msgCodeFilterModel;
};

/**
 * @}
 */

#endif // MSGCODEFILTERWIDGET_H
