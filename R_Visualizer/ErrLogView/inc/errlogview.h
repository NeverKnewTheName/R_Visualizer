/**
 * @file	errorlogview.h
 * @author	Christian Neuberger
 *
 * \brief Class to interact with the Error Log View Dialog
 *
 *
 *
 */

#ifndef ERRORLOGVIEW_H
#define ERRORLOGVIEW_H

#include "errlogmodel.h"

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class ErrorLogView;
}

class ErrorLogView : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorLogView(QWidget *parent = 0);
    ~ErrorLogView();

    ErrLogModel *getErrLogModel() const;
    void setErrLogModel(ErrLogModel *value);

private slots:

    void on_savePB_clicked();

    void on_openPB_clicked();

    void on_closePB_clicked();

    void on_addErrConfPB_clicked();

    void on_removeErrConfPB_clicked();

    void on_saveErrConfPB_clicked();

    void on_openErrConfPB_clicked();

private:
    Ui::ErrorLogView *ui;
    ErrLogModel *errLogModel;
};

#endif // ERRORLOGVIEW_H
