#ifndef ERRLOGMODEL_H
#define ERRLOGMODEL_H

#include "can_packet.h"
#include "hugeqvector.h"
#include "errorlogentry.h"

#include <QAbstractTableModel>

class ErrLogModel : public QAbstractTableModel
{
public:
    ErrLogModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    void addErrEntry(ErrorLogEntry *errLogEntry);

    enum HeaderCols
    {
        COL_TIMESTAMP,
        COL_TX_ERR_CNTR,
        COL_RX_ERR_CNTR,
        COL_DETAILS,
        COL_NR_OF_COLS
    };
private:
    HugeQVector<ErrorLogEntry> errLogStore;


private slots:
    void errLogMsgReceived(CAN_PacketPtr ptr);

signals:
    void rowAppended(unsigned int rowNr);
    void rowsAdded(unsigned int nrOfRowsAdded);
};

#endif // ERRLOGMODEL_H
