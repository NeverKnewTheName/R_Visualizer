#include "idmodel.h"

#include <QBrush>
#include <QJsonDocument>
#include <QJsonArray>


IDModel::IDModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int IDModel::rowCount(const QModelIndex &parent) const
{
    return idStore.size();
}

int IDModel::columnCount(const QModelIndex &parent) const
{
    return COL_NR_OF_COLS;
}

QVariant IDModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        if(col == COL_ID) return QString("0x%1").arg(idStore[row]->getId()/*decimal*/, 4/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/); // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
        if(col == COL_NAME) return idStore[row]->getName();
        if(col == COL_COLOR) return idStore[row]->getColor().name();
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
        QBrush bgBrush(idStore[row]->getColor());
        return bgBrush;
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

bool IDModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

QVariant IDModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_ID:
                return QString("ID");
                break;
            case COL_NAME:
                return QString("Name");
                break;
            case COL_COLOR:
                return QString("Color");
                break;
            }
        }
    }
    return QVariant();
}


void IDModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    qDeleteAll(idStore);
    idStore.clear();
    endResetModel();
}

void IDModel::add(IDRep *idRep)
{
    int newRow = idStore.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    this->idStore.append(idRep);
    endInsertRows();
}

QString IDModel::getNameToID(int id)
{

}

QColor IDModel::getColorToID(int id)
{

}

QByteArray IDModel::parseToJSON()
{
    QJsonArray jsonMsgsArr;
    for(int i = 0; i < idStore.size();++i)
    {
        IDRep *idRep = this->idStore.at(i);
        jsonMsgsArr.append(idRep->parseOUT());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Compact);
}

void IDModel::parseFromJSON(QByteArray jsonFile)
{
    this->clear();
    //    QJsonDocument jsonMsgs = QJsonDocument::fromBinaryData(jsonFile);
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        IDRep *newIDRep = new IDRep();
        newIDRep->parseIN(item.toObject());
        this->add(newIDRep);
    }
}
