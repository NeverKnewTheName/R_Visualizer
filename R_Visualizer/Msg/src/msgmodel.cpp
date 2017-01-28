#include "msgmodel.h"

#include "msg.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFont>
#include <QBrush>
#include <QTextEdit>

#include <QDebug>


MsgModel::MsgModel(QObject *parent) :
    QAbstractTableModel(parent)
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
        if(col == COL_NAME) return msgs.at(row)->getId();
        if(col == COL_MESSAGE) return QString("Code: 0x%1\nData: %2").arg(msgs.at(row)->getCode()).arg(msgs.at(row)->getDataAsString());
//        if(col == COL_MESSAGE) return QTextEdit(QString("RABL\nRABL\nRABL\nRABL\n"));
        break;
    case Qt::SizeHintRole:
//        return QSize(100,40);
        return msgs.at(row)->getMsgSizeHint();
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
        return QVariant::fromValue(static_cast<void*>(this->msgs.at(row)));
        break;
    case Qt::UserRole +2:  // return Code of the line
        return this->msgs.at(row)->getCode();
        break;
    case Qt::UserRole +3: // return raw data
        if(col == COL_TIMESTAMP) return msgs.at(row)->getTimestamp();
        if(col == COL_NAME) return msgs.at(row)->getId();
        if(col == COL_MESSAGE) return msgs.at(row)->getCode();
        break;
    case Qt::UserRole +4:// return Keys for PixmapCache
        if(col == COL_TIMESTAMP)
        {
            return QString("PxmpCach_TmStmp%1").arg(msgs.at(row)->getTimestamp().toString("dd.MM.yyyy - hh:mm:ss.zzz"));
        }
        if(col == COL_NAME)
        {
            return QString("PxmpCach_ID%1").arg(msgs.at(row)->getId());
        }
        if(col == COL_MESSAGE)
        {
            QString MsgDataKey(QString("PxmpCach_MsgData_ID%1_Code%2_Data")
                    .arg(msgs.at(row)->getCode())
                    .arg(msgs.at(row)->getCode())
                               );
            for(auto & dataByte : msgs.at(row)->getData()->DataBytes)
            {
                MsgDataKey.append(QString::number(dataByte));
            }
            return MsgDataKey;
        }
        break;
    }

    return QVariant();
}

bool MsgModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index)
    Q_UNUSED(value)
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

bool MsgModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int msgModelSize = msgs.size();
    if((row+count) < msgModelSize)
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

void MsgModel::removeRow(int row, const QModelIndex &parent)
{
    int msgModelSize = msgs.size();
    if(row < msgModelSize)
    {
        beginRemoveRows(parent, row, row);
        msgs.remove(row);
        endRemoveRows();
    } else
    {
        qDebug() << "Index of row to remove not in model";
    }
}

void MsgModel::addMsg(Msg *msg)
{
    int newRow = msgs.size();
    beginInsertRows(QModelIndex(),newRow,newRow);
    msgs.append(msg);
    endInsertRows();
    emit rowInvalidated(createIndex(newRow,2));
    emit rowInvalidated(createIndex(newRow,1));
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

HugeQVector<Msg> MsgModel::getMsgs() const
{
    return msgs;
}

void MsgModel::setMsgs(const HugeQVector<Msg> value)
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

void MsgModel::messageReceived(Msg *msg)
{
    addMsg(msg);
}

