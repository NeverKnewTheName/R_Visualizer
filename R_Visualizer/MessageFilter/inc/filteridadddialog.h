/**
 * \file filteridadddialog.h
 * \author Christian Neuberger
 * \date 2017-02-08
 * 
 * \brief Small dialog for addings #MsgIDType to the #MessageFilter ID filter
 */
#ifndef FILTERIDADDDIALOG_H
#define FILTERIDADDDIALOG_H

#include <QDialog>

class IDModel;

namespace Ui {
class FilterIDAddDialog;
}

class FilterIDAddDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a new FilterIDAddDialog object
     * 
     * \param[in] idModelForCompletion This #IDModel is used for the autocompletion feature
     * \param[in] parent The parent widget of this dialog
     */
    explicit FilterIDAddDialog(const IDModel &idModelForCompletion, QWidget *parent = 0);
    ~FilterIDAddDialog();

private:
    Ui::FilterIDAddDialog *ui;
    /**
     * \brief The #IDModel that is used for the autocompletion feature and name to #MsgIDType resolution
     */
    const IDModel &idModelForCompletion;

signals:
    /**
     * \brief Commit sends the ID that was entered in the dialog as a #MsgIDType
     */
    void commit(const MsgIDType idToCommit);

private slots:
    /**
     * \brief This slot is called internally when the contents of the dialog are ready to commit
     * 
     * The readyToCommit slot converts the dialog input to a #MsgIDType and emits the #commit signal
     * subsequently with the retrieved #MsgIDType.
     */
    void readyToCommit();
};

#endif // FILTERIDADDDIALOG_H
