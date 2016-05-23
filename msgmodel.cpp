#include "msgmodel.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <QFont>
#include <QBrush>

MsgModel::MsgModel(QObject *parent) : QAbstractTableModel(parent)
{
}

MsgModel::~MsgModel()
{
    qDeleteAll(msgs);
    msgs.clear();
}

int MsgModel::rowCount(const QModelIndex &parent) const
{
    return msgs.size();
}

int MsgModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant MsgModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        if(col == 0) return msgs[row]->getTimestamp();
        if(col == 1) return msgs[row]->getId();
        if(col == 2) return msgs[row]->getMessage();
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
//        if(row == 1 && col == 2)
//        {
//            QBrush redBackground(Qt::red);
//            return redBackground;
//        }
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
                case 0:
                    return QString("Timestamp");
                case 1:
                    return QString("Name");
                case 2:
                    return QString("Message");
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
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void MsgModel::parseFromJSON(QByteArray jsonFile)
{
    qDeleteAll(msgs);
    msgs.clear();
    QJsonArray jsonMsgsArr = QJsonDocument::fromBinaryData(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        Msg *newMsg = new Msg();
        newMsg->parseIN(item.toObject());
        this->addMsg(newMsg);
    }
}

