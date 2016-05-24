#include "msgtypemodel.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <QBrush>

MsgTypeModel::MsgTypeModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int MsgTypeModel::rowCount(const QModelIndex &parent) const
{
    return msgTypeStore.size();
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
        if(col == COL_CODE) return QString("0x%1").arg(msgTypeStore[row]->getCode()/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/); // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
        if(col == COL_MESSAGE) return msgTypeStore[row]->getMessage();
        if(col == COL_COLOR) return msgTypeStore[row]->getColor().name();
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
        QBrush bgBrush(msgTypeStore[row]->getColor());
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
            case COL_MESSAGE:
                return QString("Message");
                break;
            case COL_COLOR:
                return QString("Color");
                break;
            }
        }
    }
    return QVariant();
}

void MsgTypeModel::add(MsgTypeRep *msgTypeRep)
{
    int newRow = msgTypeStore.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    this->msgTypeStore.append(msgTypeRep);
    endInsertRows();
}

void MsgTypeModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    qDeleteAll(msgTypeStore);
    msgTypeStore.clear();
    endResetModel();
}

QByteArray MsgTypeModel::parseToJSON()
{
    QJsonArray jsonMsgsArr;
    for(int i = 0; i < msgTypeStore.size();++i)
    {
        MsgTypeRep *newMsgTypeRep = this->msgTypeStore.at(i);
        jsonMsgsArr.append(newMsgTypeRep->parseOUT());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Compact);
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
        this->add(newMsgTypeRep);
    }
}
