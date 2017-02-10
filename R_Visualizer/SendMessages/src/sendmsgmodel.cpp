#include "sendmsgmodel.h"

#include "msg.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFont>
#include <QBrush>
#include <QTextEdit>

#include <QDebug>


SendMsgModel::SendMsgModel(const size_t nrOfMessagesToDisplay,
                   const FilterIDStore &filterIDModel,
                   const FilterCodeStore &filterCodeModel,
                   const FilterTimestampStore &filterTimestampModel,
                   QObject *parent) :
    QAbstractTableModel(parent),
    NrOfMessagesToDisplay(nrOfMessagesToDisplay),
    msgBuffer(nrOfMessagesToDisplay),
    FilterIDModel(filterIDModel),
    FilterCodeModel(filterCodeModel),
    FilterTimestampModel(filterTimestampModel)
{
}

SendMsgModel::~SendMsgModel()
{
    this->clear();
}

int SendMsgModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgBuffer.size();
}

int SendMsgModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COL_NR_OF_COLS;
}

QVariant SendMsgModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    const Msg &msgAtIndex = msgPacketStorage.at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        // returns only displayable data
        switch(col)
        {
            case COL_ID:
                return msgAtIndex.getId();
                break;
            case COL_CODE:
                return msgAtIndex.getCode();
                break;
            case COL_DATA:
                return msgAtIndex.getDataAsString();
                break;
        }
        break;
    case Qt::SizeHintRole:
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        //Background is drawn by delegate
        switch(col)
        {
            case COL_ID:
                return ;
                break;
            case COL_CODE:
                return ;
                break;
            case COL_DATA:
                return ;
                break;
        }
        break;
    case Qt::TextAlignmentRole:
        return Qt::TextWordWrap;
        break;
    case Qt::CheckStateRole:
        break;
    case DataUsr_RawData: //Qt::UserRole+0
        switch(col)
        {
            case COL_ID:
                return ;
                break;
            case COL_CODE:
                return ;
                break;
            case COL_DATA:
                return ;
                break;
        }
        break;
    case Qt::UserRole +1:  // return Data
        //ToTHINK!!! DO NOT USE ADDRESSES OF DATASTORAGE...
        return QVariant::fromValue(static_cast<void*>(&msgAtIndex));
        break;
    }

    return QVariant();
}

bool SendMsgModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index)
    Q_UNUSED(value)
    //ToDO if msgs should be editable
    if (role == Qt::EditRole)
    {
        //msgs.at(index.row()) = value.toString();

        //emit editCompleted( result );
    }
    return true;
}

QVariant SendMsgModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_ID:
                return QString("Name");
                break;
            case COL_CODE:
                return QString("Code");
                break;
            case COL_DATA:
                return QString("Data");
                break;
            }
        }
    }
    return QVariant();
}

bool SendMsgModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int msgModelSize = msgPacketStorage.size();
    if((row+count) < msgModelSize)
    {
        while(count--)
        {
            removeRow(row+count, parent);
        }
        return true;
    }
    else
    {
        return false;
    }
}

void SendMsgModel::removeRow(int row, const QModelIndex &parent)
{
    int msgModelSize = msgPacketStorage.size();
    if(row < msgModelSize)
    {
        beginRemoveRows(parent, row, row);
        msgPacketStorage.remove(row);
        endRemoveRows();
    } else
    {
        qDebug() << "Index of row to remove not in model";
    }
}

void SendMsgModel::addMsg(const Msg &msg)
{
    int newRow = msgPacketStorage.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    msgPacketStorage.append(msg);
    endInsertRows();
}

void SendMsgModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    msgPacketStorage.clear();
    endResetModel();
}

QByteArray SendMsgModel::ParseToJSON()
{
    QJsonArray jsonMsgsArr;
    for(int i = 0; i < msgBuff.size();++i)
    {
        const Msg &msg = msgPacketStorage.at(i);
        jsonMsgsArr.append(msg.parseOUT());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void SendMsgModel::ParseFromJSON(const QByteArray &jsonFile)
{
    this->clear();
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        const Msg &newMsg(item.toObject);
        addMsg(newMsg);
    }
}
