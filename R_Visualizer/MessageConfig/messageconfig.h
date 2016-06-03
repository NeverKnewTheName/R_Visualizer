#ifndef MESSAGECONFIG_H
#define MESSAGECONFIG_H

#include <QWidget>
#include "idmodel.h"
#include "msgtypemodel.h"
#include "userrolemngr.h"
#include "filteridstore.h"
#include "filtercodestore.h"
#include "filtertimestampstore.h"

class MainWindow;

namespace Ui {
class MessageConfig;
}

class MessageConfig : public QWidget
{
    Q_OBJECT

public:
    explicit MessageConfig(IDModel *idModel, MsgTypeModel *msgTypeModel, QWidget *parent = 0);
    ~MessageConfig();
    FilterIDStore *getFilterIDModel() const;

private:
    Ui::MessageConfig *ui;
    void initIDTableView();
    void initMsgTypeTableView();
    void initFilterIDListView();
    void initFilterCodeListView();

    friend class MainWindow;

    IDModel *idModel;
    MsgTypeModel *msgTypeModel;
    FilterIDStore *filterIDModel;
    FilterCodeStore *filterCodeModel;
    FilterTimestampStore *filterTimestampStore;

signals:
    void sgnlIdAddFinished(const int id, const QString name, const QColor color);
    void sgnlMsgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color);
    void startEditFilterID(QModelIndex &);
    void filterIDstateChange(bool enabled);

private slots:
    void idAddFinished(const int id, const QString name, const QColor color);
    void msgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color);
    void filterIDAdded(unsigned int pos);

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
