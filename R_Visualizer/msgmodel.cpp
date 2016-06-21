#include "msgmodel.h"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>

#include <QFont>
#include <QBrush>

MsgModel::MsgModel(QObject *parent) : QAbstractTableModel(parent)
{
}

MsgModel::~MsgModel()
{
    this->clear();
}

int MsgModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgs.size();
}

int MsgModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COL_NR_OF_COLS;
}

QVariant MsgModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        // returns only displayable data
        if(col == COL_TIMESTAMP) return msgs.at(row)->getTimestamp().toString("dd.MM.yyyy - hh:mm:ss.zzz");
        if(col == COL_NAME) return this->msgs.at(row)->getId();
        if(col == COL_MESSAGE) return msgs.at(row)->getDataAsString();
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        //Background is drawn by delegate
        break;
    case Qt::TextAlignmentRole:
        return Qt::TextWordWrap;
        break;
    case Qt::CheckStateRole:
        break;
    case Qt::UserRole +1:  // return Data
    {
        return QVariant::fromValue(this->msgs.at(row)->getData());
    }
        break;
    case Qt::UserRole +2:  // return Code of the line
        return this->msgs.at(row)->getCode();
        break;
    case Qt::UserRole +3: // return raw data
        if(col == COL_TIMESTAMP) return msgs.at(row)->getTimestamp();
        if(col == COL_NAME) return this->msgs.at(row)->getId();
        if(col == COL_MESSAGE) return this->msgs.at(row)->getCode();
        break;
    }

    return QVariant();
}

bool MsgModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //ToDO if msgs should be editable
    if (role == Qt::EditRole)
    {
        //save value from editor to member m_gridData
        //msgs.at(index.row()) = value.toString();
        //for presentation purposes only: build and emit a joined string

        //emit editCompleted( result );
    }
    return true;
}

QVariant MsgModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_TIMESTAMP:
                return QString("Timestamp");
                break;
            case COL_NAME:
                return QString("Name");
                break;
            case COL_MESSAGE:
                return QString("Message");
                break;
            }
        }
    }
    return QVariant();
}

void MsgModel::addMsg(Msg *msg)
{
    int newRow = msgs.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    this->msgs.append(msg);
    endInsertRows();
    emit rowsAdded(1);
    emit rowAppended(newRow);
}

void MsgModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
//    qDeleteAll(msgs);
    msgs.clear();
    endResetModel();
}

HugeQVector MsgModel::getMsgs() const
{
    return msgs;
}

void MsgModel::setMsgs(const HugeQVector value)
{
    this->clear();
    beginInsertRows(QModelIndex(),0,value.size());
    int size = value.size();
    for( int i = 0; i < size; i++)
    {
        msgs.append(value.at(i));
    }
    endInsertRows();
}

QByteArray MsgModel::parseToJSON()
{
    QJsonArray jsonMsgsArr;
    for(int i = 0; i < msgs.size();++i)
    {
        Msg *msg = this->msgs.at(i);
        jsonMsgsArr.append(msg->parseOUT());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void MsgModel::parseFromJSON(QByteArray jsonFile)
{
    this->clear();
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        Msg *newMsg = new Msg();
        newMsg->parseIN(item.toObject());
        this->addMsg(newMsg);
    }
}

void MsgModel::messageReceived(CAN_PacketPtr ptr)
{
    Data_PacketPtr packet = qSharedPointerDynamicCast<Data_Packet>(ptr);
    QDateTime timeStamp = ptr->timestamp();
    unsigned int id = packet->frame().ID_Standard;
    QByteArray canData = packet->frame().data;

    this->addMsg(new Msg(timeStamp, id, canData));
}

