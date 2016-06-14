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
        if(col == COL_CODENAME) return msgTypePropStore.value(codeStore[row])->getCodeName();
        if(col == COL_MESSAGEFORMAT) return msgTypePropStore.value(codeStore[row])->getMessageFormat();
        if(col == COL_COLOR) return msgTypePropStore.value(codeStore[row])->getColor().name();
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
        QBrush bgBrush(msgTypePropStore.value(codeStore[row])->getColor());
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
        if(col == COL_CODE) ;
        if(col == COL_CODENAME) msgTypePropStore.value(codeStore[row])->setCodeName(value.value<QString>());
        if(col == COL_MESSAGEFORMAT ) msgTypePropStore.value(codeStore[row])->setMessageFormat(value.value<QString>());
        if(col == COL_COLOR) msgTypePropStore.value(codeStore[row])->setColor(value.value<QColor>());
        emit dataChanged(index, index);
        emit internalModelChanged();
        return true;
        break;
    }
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

void MsgTypeModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row);
    delete msgTypePropStore.value(codeStore.at(row));
    msgTypePropStore.remove(codeStore.at(row));
    codeStore.remove(row);
    endRemoveRows();
    emit internalModelChanged();
}

Qt::ItemFlags MsgTypeModel::flags(const QModelIndex &index) const
{
    int col = index.column();

    if(col == COL_CODE) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if((col == COL_CODENAME) || ( col == COL_MESSAGEFORMAT ) || (col == COL_COLOR) ) return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::NoItemFlags;
}

void MsgTypeModel::add(unsigned int code, MsgTypeRep *msgTypeRep)
{
    int newRow = this->codeStore.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    this->codeStore.append(code);
    this->msgTypePropStore[code] = msgTypeRep;
    endInsertRows();
    emit internalModelChanged();
}

void MsgTypeModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    qDeleteAll(msgTypePropStore);
    msgTypePropStore.clear();
    codeStore.clear();
    endResetModel();
    emit internalModelChanged();
}

QString MsgTypeModel::getNameToCode(unsigned int code) const
{
    MsgTypeRep *msgTypeRep = msgTypePropStore.value(code);

    if(msgTypeRep != Q_NULLPTR)
        return msgTypeRep->getCodeName();
    else
        return QString("");
}

unsigned int MsgTypeModel::getCodeToName(const QString &name) const
{
    for( auto &msgTR : msgTypePropStore )
    {
        if(!name.compare(msgTR->getCodeName(),Qt::CaseInsensitive))
            return msgTR->getCode();
    }
    return 0;
}

QString MsgTypeModel::getMessageToCode(unsigned int code) const
{
    MsgTypeRep *msgTypeRep = msgTypePropStore.value(code);

    if(msgTypeRep != Q_NULLPTR)
    {

        return msgTypeRep->getMessageFormat();
    }
    else
        return QString("");
}

QColor MsgTypeModel::getColorToCode(unsigned int code) const
{
    MsgTypeRep *msgTypeRep = msgTypePropStore.value(code);

    if(msgTypeRep != Q_NULLPTR)
        return msgTypeRep->getColor();
    else
        return QColor();
}

int MsgTypeModel::getNrLinesToCode(unsigned int code)
{
    //qDebug() << __FUNCTION__;
    MsgTypeRep *msgTypeRep = msgTypePropStore.value(code);

    if(msgTypeRep != Q_NULLPTR)
    {
        return msgTypeRep->getMessageFormat().count("\n");
    }
    else
    {
        return 1;
    }
}

QStringList MsgTypeModel::getAllCodeNames() const
{
    QStringList names;
    for(auto msgTypeRep : this->msgTypePropStore )
    {
        names.append(msgTypeRep->getCodeName());
    }
    return names;
}

QByteArray MsgTypeModel::parseToJSON()
{
    QJsonArray jsonMsgsArr;
    for(int i = 0; i < this->codeStore.size();++i)
    {
        MsgTypeRep *newMsgTypeRep = this->msgTypePropStore.value(this->codeStore.at(i));
        jsonMsgsArr.append(newMsgTypeRep->parseOUT());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void MsgTypeModel::parseFromJSON(QByteArray jsonFile)
{
    this->clear();
    //    QJsonDocument jsonMsgs = QJsonDocument::fromBinaryData(jsonFile);
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        MsgTypeRep *newMsgTypeRep = new MsgTypeRep();
        newMsgTypeRep->parseIN(item.toObject());
        this->add(newMsgTypeRep->getCode(), newMsgTypeRep);
    }
}
