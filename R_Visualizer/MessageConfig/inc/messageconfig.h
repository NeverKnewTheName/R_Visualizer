#ifndef MESSAGECONFIG_H
#define MESSAGECONFIG_H

#include <QWidget>
#include "idmodel.h"
#include "msgtypemodel.h"
#include "userrolemngr.h"

class MainWindow;

namespace Ui {
class MessageConfig;
}

class MessageConfig : public QWidget
{
    Q_OBJECT

public:
    explicit MessageConfig(IDModel &idModel, MsgTypeModel &msgTypeModel, QWidget *parent = 0);
    ~MessageConfig();
//    FilterIDStore &getFilterIDModel() const;
//    FilterCodeStore &getFilterCodeModel() const;
//    FilterTimestampStore &getFilterTimestampModel() const;

    MsgTypeModel &getMsgTypeModel() const;

    FilterCodeStore &getFilterCodeModel();

    FilterTimestampStore &getFilterTimestampModel();

    FilterIDStore &getFilterIDModel();

private:
    Ui::MessageConfig *ui;
    void initIDTableView();
    void initMsgTypeTableView();
    void initFilterIDListView();
    void initFilterCodeListView();

    friend class MainWindow;

    IDModel &idModel;
    MsgTypeModel &msgTypeModel;

    bool idFilterEnabled;
    bool codeFilterEnabled;
    bool timeStampFilterFromEnabled;
    bool timeStampFilterToEnabled;

signals:
    void sgnlIdAddFinished(const MsgIDType id, const QString &name, const QColor &color);
    void sgnlMsgTypeAddFinished(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color);
    void startEditFilterID(QModelIndex &);
    void filterIDstateChange(bool enabled);
    void filterCodestateChange(bool enabled);
    void filterTimestampFromStateChange(bool enabled);
    void filterTimestampToStateChange(bool enabled);
    void sgnl_timestampFromChanged(QDateTime newFromDateTime);
    void sgnl_timestampToChanged(QDateTime newToDateTime);

private slots:
    void idAddFinished(const MsgIDType id, const QString &name, const QColor &color);
    void msgTypeAddFinished(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color);
    void filterIDAdded(unsigned int pos);
    void slt_timestampFromChanged();
    void slt_timestampToChanged();

    void applyRole(UserRoleMngr::UserRole roleToSwitchTo);

    void on_idStoreBtn_clicked();
    void on_idLoadBtn_clicked();
    void on_msgTypeStoreBtn_clicked();
    void on_msgTypeLoadBtn_clicked();
    void on_idAddBtn_clicked();
    void on_msgTypeAddBtn_clicked();
    void on_idRmvBtn_clicked();
    void on_msgTypeRmvBtn_clicked();
    void on_enableIDFilterPushButton_clicked();
    void on_addFilterIDPushButton_clicked();
    void on_rmvFilterIDPushButton_clicked();
    void on_enableCodeFilterPushButton_clicked();
    void on_addFilterCodePushButton_clicked();
    void on_rmvFilterCodePushButton_clicked();
    void on_enableTimestampFromFilterPushButton_clicked();
    void on_enableTimestampToFilterPushButton_clicked();
};

#endif // MESSAGECONFIG_H
