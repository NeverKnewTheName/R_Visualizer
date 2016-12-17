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
        if(col == COL_ID) return QString("0x%1").arg(idStore[row]/*decimal*/, 4/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/); // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
        if(col == COL_NAME) return idPropStore.value(idStore[row]).getName();
        if(col == COL_COLOR) return idPropStore.value(idStore[row]).getColor().name();
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
        QBrush bgBrush(idPropStore.value(idStore[row]).getColor());
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
    int row = index.row();
    int col = index.column();
    switch(role)
    {
    case Qt::EditRole:
        if(col == COL_NAME) idPropStore[idStore[row]].setName(value.value<QString>());
        if(col == COL_COLOR) idPropStore[idStore[row]].setColor(value.value<QColor>());
        emit dataChanged(index, index);
        return true;
        break;
    }
    return false;
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

bool IDModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int modelSize = idStore.size();
    if(modelSize || ((row+count) < modelSize))
    {
        while(count--)
            removeRow(row+count, parent);
        return true;
    }
    else
    {
        return false;
    }
}

void IDModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    idPropStore.remove(idStore.at(row));
    idStore.remove(row);
    endRemoveRows();
}

Qt::ItemFlags IDModel::flags(const QModelIndex &index) const
{
    int col = index.column();

    if(col == COL_ID) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if((col == COL_NAME) || (col == COL_COLOR) ) return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}


void IDModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    idPropStore.clear();
    idStore.clear();
    endResetModel();
}

quint16 IDModel::getIDToName(const QString &name) const
{
    for( auto &idProp : idPropStore )
    {
        if(!name.compare(idProp.getName(),Qt::CaseInsensitive))
            return idPropStore.key(idProp);
    }
    return 0;
}

void IDModel::add(const IDRep &idRep)
{
    int newRow = idStore.size();
    const quint16/*ToDO MsgIDType*/ id = idRep.getId();
    beginInsertRows(QModelIndex(),newRow,newRow);
    idStore.append(id);
    idPropStore.remove(id);
    idPropStore.insertMulti(id, idRep); //idRep has no AssignmentOperator...thus we need to remove the Key and create a new one...
    endInsertRows();
}

QString IDModel::getNameToID(const quint16/*ToDO MsgIDType*/ id) const
{
    if(idPropStore.contains(id))
    {
        return idPropStore[id].getName();
    }

    return QString("");
}

QColor IDModel::getColorToID(const quint16/*ToDO MsgIDType*/ id) const
{
    if(idPropStore.contains(id))
    {
        return idPropStore[id].getColor();
    }

    return QColor();
}

QByteArray IDModel::parseToJSON() const
{
    QJsonArray jsonMsgsArr;
    for(quint16 id : idStore)
    {
        QJsonObject jsonSveObj = idPropStore[id].parseOUT();
        jsonMsgsArr.append(jsonSveObj);
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void IDModel::parseFromJSON(const QByteArray &jsonFile)
{
    this->clear();
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto &&item : jsonMsgsArr)
    {
        add(IDRep::createObjFromJson(item.toObject()));
    }
}

const QPixmap &IDModel::paintID(const QRect &boundingRect, const quint16 id)
{
    return idPropStore[id].paintIDRep(boundingRect);
}

QStringList IDModel::getAllIDNames() const
{
    QStringList names;
    for(auto idRep : idPropStore)
    {
        names.append(idRep.getName());
    }
    return names;
}
