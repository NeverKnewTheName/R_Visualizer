#include "errlogmodel.h"
#include "errorlogentry.h"
#include "hugeqvector.h"

#include <QDebug>

#include "fileparser.h"

ErrLogModel::ErrLogModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

int ErrLogModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return this->errLogStore.size();
}

int ErrLogModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COL_NR_OF_COLS;
}

QVariant ErrLogModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        // returns only displayable data
        if(col == COL_TIMESTAMP) return errLogStore.at(row)->getTimestamp().toString("dd.MM.yyyy - hh:mm:ss.zzz");
        if(col == COL_DETAILS) return errLogStore.at(row)->getDetailString();
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        break;
    case Qt::TextAlignmentRole:
        return Qt::TextWordWrap;
        break;
    case Qt::CheckStateRole:
        break;
    }

    return QVariant();
}

QVariant ErrLogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_TIMESTAMP:
                return QString("Timestamp");
                break;
            case COL_DETAILS:
                return QString("Details");
                break;
            }
        }
    }
    return QVariant();
}


bool ErrLogModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(row)
    Q_UNUSED(count)
    Q_UNUSED(parent)
    return true;
}

void ErrLogModel::addErrEntry(ErrorLogEntry *errLogEntry)
{
    int newRowIndex = this->errLogStore.size();
    beginInsertRows(QModelIndex(),newRowIndex,newRowIndex);
    this->errLogStore.append(errLogEntry);
    endInsertRows();
//    emit rowsAdded(1);
//    emit rowAppended(newRow);
}

void ErrLogModel::accept(FileParser *visitor)
{
    //ToDo
    //visitor->visit(*this);
}

void ErrLogModel::errLogMsgReceived(ErrorLogEntry *errLogEntry)
{
        this->addErrEntry(errLogEntry);
}
