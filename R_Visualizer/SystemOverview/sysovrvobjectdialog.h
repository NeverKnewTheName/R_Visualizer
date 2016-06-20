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
    QGraphicsScene *scene;

    enum Shapetypes
    {
        ObjShape_Rectangle,
        ObjShape_Square,
        ObjShape_Circle,
        ObjShape_Triangle
    }ObjShapeTypes;

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
};

#endif // SYSOVRVOBJECTDIALOG_H
