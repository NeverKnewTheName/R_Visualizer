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
        if(col == COL_TIMESTAMP) return msgs[row]->getTimestamp();
        if(col == COL_NAME)
        {
            int id = this->msgs.at(row)->getId();
            QString name = this->idModel->getNameToID(id);
            if(name.isEmpty())
            {
                // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
                return QString("0x%1").arg(id/*decimal*/, 4/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
            } else
            {
                return name;
            }
        }
        if(col == COL_MESSAGE)
        {
            // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
            //return QString("0x%1").arg(msgs[row]->getData()/*decimal*/, 16/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
            QString message;
            unsigned int code = msgs[row]->getCode();
            QString codeName = this->msgTypeModel->getMessageToCode(code);
            if(codeName.isEmpty())
            {
                message.append(QString("Code:\t"));
                message.append(QString("0x%1").arg(code/*decimal*/, 4/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/) );
            }
            else
            {
                message.append(QString("Code:\t"));
                message.append(codeName);
            }
            message.append(QString("\n"));
            message.append(QString("Message:\t"));
            message.append(msgs[row]->getMessageAsString());
            return message;
            //return msgs[row]->getDataAsString();
            //return msgs[row]->getData();
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
        } else if( col == COL_MESSAGE)
        {
            return QBrush(this->msgTypeModel->getColorToCode(this->msgs.at(row)->getCode()));
        }
        //        if(row == 1 && col == 2)
        //        {
        //            QBrush redBackground(Qt::red);
        //            return redBackground;
        //        }
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

