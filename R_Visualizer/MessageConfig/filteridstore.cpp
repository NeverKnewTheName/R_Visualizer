#include "filteridstore.h"

#include <QBrush>
#include <QDebug>

FilterIDStore::FilterIDStore(IDModel *idModel, QObject *parent) : QAbstractListModel(parent), idModel(idModel)
{

}

int FilterIDStore::rowCount(const QModelIndex &parent) const
{
    idStore.size();
}

QVariant FilterIDStore::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    switch(role)
    {
    case Qt::DisplayRole:
    {
        return idStore.at(row);
//        unsigned int id = idStore.at(row);
//        QString idName = idModel->getNameToID(id);
//        if(idName.isEmpty())
//        {
//            return QString("0x%1").arg(id/*decimal*/, 4/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/); // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
//        }
//        else
//        {
//            return idName;
//        }
    }
        break;
    case Qt::FontRole:
        //        if(row == 0 && col == 0)
        //        {
        //            QFont boldFont;
        //            boldFont.setBold(true);
        //            return boldFont;
        //        }
        break;
    case Qt::BackgroundRole:
    {
//        QBrush bgBrush(idModel->getColorToID(idStore.at(row)));
//                return bgBrush;
    }
        break;
    case Qt::TextAlignmentRole:
        //        if(row == 1 && col == 1)
        //        {
        //            return Qt::AlignRight + Qt::AlignVCenter;
        //        }
        break;
    case Qt::CheckStateRole:
        //        if(row == 1 && col == 0)
        //        {
        //            return Qt::Checked;
        //        }
        break;
    }
    return QVariant();
}

QVariant FilterIDStore::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            return QString("ID/Name");
        }
    }
    return QVariant();
}

bool FilterIDStore::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    switch(role)
    {
    case Qt::EditRole:
        idStore[row] = value.value<int>();
        emit internalModelChanged();
        return true;
        break;
    }
}

Qt::ItemFlags FilterIDStore::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void FilterIDStore::addID(unsigned int id)
{
    beginInsertRows(QModelIndex(), idStore.size(), idStore.size());
    idStore.append(id);
    endInsertRows();
    tempIndex = this->index(idStore.size()-1);
    qDebug() << "Index:" << tempIndex.row();
    emit rowAdded(tempIndex);
}

void FilterIDStore::addID(QString &idString)
{
    beginInsertRows(QModelIndex(), idStore.size(), idStore.size());
    idStore.append(idString.toUInt());
    endInsertRows();
    tempIndex = this->index(idStore.size()-1);
    qDebug() << "Index:" << tempIndex.row();
    emit rowAdded(tempIndex);
}

void FilterIDStore::removeID(QModelIndex &index)
{
    beginRemoveRows(QModelIndex(),index.row(), index.row());
    idStore.remove(index.row());
    endRemoveRows();
    emit internalModelChanged();
}

bool FilterIDStore::containsID(unsigned int id)
{
    return idStore.contains(id);
}
