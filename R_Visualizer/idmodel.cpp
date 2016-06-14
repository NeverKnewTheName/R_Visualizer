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
        if(col == COL_NAME) return idPropStore.value(idStore[row])->getName();
        if(col == COL_COLOR) return idPropStore.value(idStore[row])->getColor().name();
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
        QBrush bgBrush(idPropStore.value(idStore[row])->getColor());
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
        if(col == COL_ID) ;
        if(col == COL_NAME) idPropStore.value(idStore[row])->setName(value.value<QString>());
        if(col == COL_COLOR) idPropStore.value(idStore[row])->setColor(value.value<QColor>());
        emit dataChanged(index, index);
        return true;
        break;
    }
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

void IDModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row);
    delete idPropStore.value(idStore.at(row));
    idPropStore.remove(idStore.at(row));
    idStore.remove(row);
    endRemoveRows();
//    emit internalModelChanged();
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
    qDeleteAll(idPropStore);
    idPropStore.clear();
    idStore.clear();
    endResetModel();
//    emit internalModelChanged();
}

unsigned int IDModel::getIDToName(const QString &name) const
{
    for( auto &idProp : idPropStore )
    {
        if(!name.compare(idProp->getName(),Qt::CaseInsensitive))
            return idPropStore.key(idProp);
    }
    return 0;
}

void IDModel::add(int id, IDRep *idRep)
{
    int newRow = idStore.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    this->idStore.append(id);
    this->idPropStore[id] = idRep;
    endInsertRows();
//    emit internalModelChanged();
}

QString IDModel::getNameToID(int id)
{
    IDRep *idRep = idPropStore.value(id);

    if(idRep != Q_NULLPTR)
        return idRep->getName();
    else
        return QString("");
}

QColor IDModel::getColorToID(int id)
{
    IDRep *idRep = idPropStore.value(id);

    if(idRep != Q_NULLPTR)
        return idRep->getColor();
    else
        return QColor();
}

QByteArray IDModel::parseToJSON() const
{
    QJsonArray jsonMsgsArr;
    for(int i = 0; i < idStore.size();++i)
    {
        IDRep *idRep = this->idPropStore.value(this->idStore.at(i));
        QJsonObject jsonSveObj;
        jsonSveObj[QString::number(this->idStore.at(i))] = idRep->parseOUT();
        //jsonMsgsArr.append(QJsonObject(this->idStore.at(i),idRep->parseOUT()));
        jsonMsgsArr.append(jsonSveObj);
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void IDModel::parseFromJSON(QByteArray jsonFile)
{
    this->clear();
    //    QJsonDocument jsonMsgs = QJsonDocument::fromBinaryData(jsonFile);
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        IDRep *newIDRep = new IDRep();
        QJsonObject itemObj = item.toObject();
        QString id = itemObj.keys().at(0);
        newIDRep->parseIN(itemObj[id].toObject());
        this->add(id.toInt(),newIDRep);
    }
}

QHash<int, IDRep *> IDModel::getIdPropStore() const
{
    return idPropStore;
}

void IDModel::setIdPropStore(const QHash<int, IDRep *> &value)
{
    idPropStore = value;
}

QStringList IDModel::getAllIDNames() const
{
    QStringList names;
    for(auto idRep : idPropStore)
    {
        names.append(idRep->getName());
    }
    return names;
}
