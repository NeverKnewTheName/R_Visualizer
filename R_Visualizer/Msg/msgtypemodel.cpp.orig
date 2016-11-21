#include "msgtypemodel.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <QBrush>
#include <QRegularExpression>

#include <QDebug>

MsgTypeModel::MsgTypeModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int MsgTypeModel::rowCount(const QModelIndex &parent) const
{
    return codeStore.size();
}

int MsgTypeModel::columnCount(const QModelIndex &parent) const
{
    return COL_NR_OF_COLS;
}

QVariant MsgTypeModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        if(col == COL_CODE) return QString("0x%1").arg(codeStore[row]/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/); // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
        if(col == COL_CODENAME) return msgTypePropStore[codeStore[row]].getCodeName();
        if(col == COL_MESSAGEFORMAT) return msgTypePropStore[codeStore[row]].getMessageFormat();
        if(col == COL_COLOR) return msgTypePropStore[codeStore[row]].getColor().name();
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
        QBrush bgBrush(msgTypePropStore[codeStore[row]].getColor());
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

bool MsgTypeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();
    switch(role)
    {
    case Qt::EditRole:
        if(col == COL_CODENAME) msgTypePropStore[codeStore[row]].setCodeName(value.value<QString>());
        if(col == COL_MESSAGEFORMAT ) msgTypePropStore[codeStore[row]].setMessageFormat(value.value<QString>());
        if(col == COL_COLOR) msgTypePropStore[codeStore[row]].setColor(value.value<QColor>());
        emit dataChanged(index, index);
        //        emit internalModelChanged();
        return true;
        break;
    }
    return false;
}

QVariant MsgTypeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_CODE:
                return QString("Code");
                break;
            case COL_CODENAME:
                return QString("Name");
                break;
            case COL_MESSAGEFORMAT:
                return QString("Message Format");
                break;
            case COL_COLOR:
                return QString("Color");
                break;
            }
        }
    }
    return QVariant();
}

bool MsgTypeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int modelSize = codeStore.size();
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

void MsgTypeModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    msgTypePropStore.remove(codeStore.at(row));
    codeStore.remove(row);
    endRemoveRows();
}

Qt::ItemFlags MsgTypeModel::flags(const QModelIndex &index) const
{
    int col = index.column();

    if(col == COL_CODE) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if((col == COL_CODENAME) || ( col == COL_MESSAGEFORMAT ) || (col == COL_COLOR) ) return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}

void MsgTypeModel::add(const MsgTypeRep &msgTypeRep)
{
    int newRow = codeStore.size();
    const quint8/*ToDO MsgCodeType*/ code = msgTypeRep.getCode();
    beginInsertRows(QModelIndex(),newRow,newRow);
    codeStore.append(code);
    msgTypePropStore.remove(code);
    msgTypePropStore.insertMulti(code, msgTypeRep);
    endInsertRows();
    //    emit internalModelChanged();
}

void MsgTypeModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    msgTypePropStore.clear();
    codeStore.clear();
    endResetModel();
    //    emit internalModelChanged();
}

QString MsgTypeModel::getNameToCode(const quint8/*ToDO MsgCodeType*/ code) const
{
    if(msgTypePropStore.contains(code))
    {
        return msgTypePropStore[code].getCodeName();
    }
    return QString("");
}

quint8 MsgTypeModel::getCodeToName(const QString &name) const
{
    for( auto &msgTypeRep : msgTypePropStore )
    {
        if(!name.compare(msgTypeRep.getCodeName(),Qt::CaseInsensitive))
            return msgTypeRep.getCode();
    }

    return 0;
}

QString MsgTypeModel::getMessageToCode(const quint8 code) const
{
    if(msgTypePropStore.contains(code))
    {
        return msgTypePropStore[code].getMessageFormat();
    }

    return QString("");
}

QColor MsgTypeModel::getColorToCode(const quint8/*ToDO MsgCodeType*/ code) const
{
    if(msgTypePropStore.contains(code))
    {
        return msgTypePropStore[code].getColor();
    }

    return QColor();
}

int MsgTypeModel::getNrLinesToCode(const quint8 code)
{
    if(msgTypePropStore.contains(code))
    {
        return msgTypePropStore[code].getMessageFormat().count("\n");
    }

    return 1;
}

QStringList MsgTypeModel::getAllCodeNames() const
{
    QStringList names;
    for(const auto &msgTypeRep : msgTypePropStore )
    {
        names.append(msgTypeRep.getCodeName());
    }
    return names;
}

QByteArray MsgTypeModel::parseToJSON() const
{
    QJsonArray jsonMsgsArr;
    for(const quint8/*ToDO MsgCodeType*/ code : codeStore)
    {
        const MsgTypeRep &newMsgTypeRep = msgTypePropStore[code];
        jsonMsgsArr.append(newMsgTypeRep.parseOUT());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void MsgTypeModel::parseFromJSON(const QByteArray &jsonFile)
{
    this->clear();
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        add(MsgTypeRep::createObjFromJson(item.toObject()));
    }
}

const QPixmap &MsgTypeModel::paintMsgTypeRep(const QRect &boundingRect, const quint8 code)
{
    return msgTypePropStore[code].paintMsgTypeRep(boundingRect);
}
