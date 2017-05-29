/**
 * @file    errorlogview.h
 * @author  Christian Neuberger
 * \date    2016-03-20
 *
 * \brief Class to interact with the Error Log View Dialog
 */

#ifndef ERRORLOGVIEW_H
#define ERRORLOGVIEW_H

#include <QDialog>
#include <QAbstractButton>


#include "errlogmodel.h"
#include "IFileParsable.h"

namespace Ui {
class ErrorLogView;
}

/**
 * \brief The ErrorLogView
 */
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
