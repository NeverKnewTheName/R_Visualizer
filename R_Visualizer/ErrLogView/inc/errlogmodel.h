/**
 * @file	errorlogmodel.h
 * @author	Christian Neuberger
 *
 * \brief Model that maintains the Error Log.
 *
 *
 *
 */

#ifndef ERRLOGMODEL_H
#define ERRLOGMODEL_H

#include <QAbstractTableModel>
#include "hugeqvector.h"

class ErrorLogEntry;
class FileParser;

#include "IFileParsable.h"

class ErrLogModel : public QAbstractTableModel, public IFileParsable
{
public:
    enum HeaderCols
    {
        COL_TIMESTAMP,
        COL_DETAILS,
        COL_NR_OF_COLS
    };

    ErrLogModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    void addErrEntry(ErrorLogEntry *errLogEntry);

    void accept(FileParser *visitor);

private:
    HugeQVector<ErrorLogEntry> errLogStore;
    friend class MainWindow;

private slots:
    void errLogMsgReceived(ErrorLogEntry *errLogEntry);

signals:
    void rowAppended(unsigned int rowNr);
    void rowsAdded(unsigned int nrOfRowsAdded);
};

#endif // ERRLOGMODEL_H
