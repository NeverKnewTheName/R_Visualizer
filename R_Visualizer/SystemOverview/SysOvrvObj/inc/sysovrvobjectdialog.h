#ifndef SYSOVRVOBJECTDIALOG_H
#define SYSOVRVOBJECTDIALOG_H

#include "sysovrvobject.h"

#include <QDialog>
#include <QAbstractButton>
#include <QGraphicsScene>

namespace Ui {
class SysOvrvObjectDialog;
}

class SysOvrvObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SysOvrvObjectDialog(QWidget *parent = 0);
    explicit SysOvrvObjectDialog(SysOvrvObject *object, QWidget *parent = 0);
    ~SysOvrvObjectDialog();

    SysOvrvObject *curSysOvrvObject() const;
    void setCurSysOvrvObject(SysOvrvObject *curSysOvrvObject);


private:
    Ui::SysOvrvObjectDialog *ui;
    SysOvrvObject *m_curSysOvrvObject;
    SysOvrvObject *m_focusedItem;
    QGraphicsScene SysOvrvScene;
    QByteArray m_jsonObjSave;

    bool updateExisting;

    void setupDialog();

signals:
    void sgnl_commit(SysOvrvObject *obj);

private slots:
    void on_addPropertyBtn_clicked();
    void on_rmvPropertyBtn_clicked();
    void on_edtPropertyBtn_clicked();
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_edtTriggerBtn_clicked();

    void slt_objectShapeChanged(int index);
    void slt_addObjectToObject(SysOvrvObject *obj);
    void slt_focusChanged(QGraphicsItem *newItem, QGraphicsItem *oldItem);
    void slt_selectionChanged();

    void on_OpenColorPicker_clicked();
    void slt_colorChanged(const QColor &newColor);

    void on_pushButton_clicked();
    void on_objectNameLE_textEdited(const QString &arg1);
    void on_addLblBtn_clicked();
    void on_colorTransparentCheckBox_toggled(bool checked);
};

#endif // SYSOVRVOBJECTDIALOG_H
