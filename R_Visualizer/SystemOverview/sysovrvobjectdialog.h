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
    SysOvrvObject *m_svdSysOvrvObject;
    SysOvrvObject *m_focusedItem;
    QGraphicsScene *scene;
    bool updateExisting;

    void setupDialog();

signals:
    void commit(SysOvrvObject *obj);

private slots:
    void on_addPropertyBtn_clicked();

    void on_rmvPropertyBtn_clicked();

    void on_edtPropertyBtn_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_edtTriggerBtn_clicked();

    void objectShapeChanged(int index);
    void addObjectToObject(SysOvrvObject *obj);
    void focusChanged(QGraphicsItem *newItem, QGraphicsItem *oldItem);
    void on_OpenColorPicker_clicked();
    void colorChanged(const QColor &newColor);
};

#endif // SYSOVRVOBJECTDIALOG_H
