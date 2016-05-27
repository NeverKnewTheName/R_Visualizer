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
    return msgs.size();
}

int MsgModel::columnCount(const QModelIndex &parent) const
{
    return COL_NR_OF_COLS;
}

QVariant MsgModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        if(col == COL_TIMESTAMP) return msgs[row]->getTimestamp().toString("dd.MM.yyyy - hh:mm:ss.zzz");
        if(col == COL_NAME)
        {
            return this->msgs.at(row)->getId();
        }
        if(col == COL_MESSAGE)
        {
            return msgs[row]->getDataAsString();
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
        if(col == COL_NAME )
        {
            return QBrush(this->idModel->getColorToID(this->msgs.at(row)->getId()));
        } /*else if( col == COL_MESSAGE)
        {
            return QBrush(this->msgTypeModel->getColorToCode(this->msgs.at(row)->getCode()));
        }*/
        break;
    case Qt::TextAlignmentRole:
        return Qt::TextWordWrap;
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
    case Qt::UserRole +1:  // return Data
    {
        return QVariant::fromValue(this->msgs.at(row)->getData());
        //return var;
    }
        break;
    case Qt::UserRole +2:  // return number of lines
        return 2;
        break;
    }

    return QVariant();
}

bool MsgModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //ToDO
    if (role == Qt::EditRole)
    {
        //save value from editor to member m_gridData
        //msgs[index.row()] = value.toString();
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

void MsgModel::setIDModel(IDModel *idModel)
{
    this->idModel = idModel;
}

void MsgModel::setMsgTypeModel(MsgTypeModel *msgTypeModel)
{
    this->msgTypeModel = msgTypeModel;
}

void MsgModel::addMsg(Msg *msg)
{
    int newRow = msgs.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    this->msgs.append(msg);
    endInsertRows();
}

void MsgModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    qDeleteAll(msgs);
    msgs.clear();
    endResetModel();
}

QVector<Msg *> MsgModel::getMsgs() const
{
    return msgs;
}

void MsgModel::setMsgs(const QVector<Msg *> &value)
{
    msgs = value;
}

QByteArray MsgModel::parseToJSON()
{
    QJsonArray jsonMsgsArr;
    for(int i = 0; i < msgs.size();++i)
    {
        Msg *msg = this->msgs.at(i);
        jsonMsgsArr.append(msg->parseOUT());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Compact);
}

void MsgModel::parseFromJSON(QByteArray jsonFile)
{
    this->clear();
    //    QJsonDocument jsonMsgs = QJsonDocument::fromBinaryData(jsonFile);
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        Msg *newMsg = new Msg();
        newMsg->parseIN(item.toObject());
        this->addMsg(newMsg);
    }
}

