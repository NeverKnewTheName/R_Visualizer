#include "MsgDataMappingModel.h"

#include <QBrush>
#include <QString>
#include <QColor>

#include <QSharedPointer>
#include <QDebug>

#include "IMsgDataFormatter.h"

#include "fileparser.h"

MsgDataMappingModel::MsgDataMappingModel(
        IMsgDataMappingStore *msgDataMappingStore,
        QObject *parent
        ) : 
    QAbstractTableModel(parent),
    msgDataMappingStore(msgDataMappingStore)
{
    if(msgDataMappingStore == Q_NULLPTR)
    {
        //ERROR
    }
    QVector<MessageTypeIdentifier> msgTypes =
            msgDataMappingStore->getContainedTypeIdentifiers();
    if(msgTypes.size())
    {
        beginInsertRows(QModelIndex(),0,msgTypes.size());
        msgIdentifierStore = msgTypes;
        endInsertRows();
    }
    connectToStore();
}

MsgDataMappingModel::~MsgDataMappingModel()
{
}

int MsgDataMappingModel::rowCount(
        const QModelIndex &parent
        ) const
{
    Q_UNUSED(parent)
    return msgIdentifierStore.size();
}

int MsgDataMappingModel::columnCount(
        const QModelIndex &parent
        ) const
{
    Q_UNUSED(parent)
    return MsgDataMappingModel::COL_NR_OF_COLS;
}

QVariant MsgDataMappingModel::headerData(
        int section,
        Qt::Orientation orientation,
        int role
        ) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case MsgDataMappingModel::COL_ID:
                return QString("ID");
                break;
            case MsgDataMappingModel::COL_Code:
                return QString("Code");
                break;
            case MsgDataMappingModel::COL_FormatString:
                return QString("Format String");
                break;
            case MsgDataMappingModel::COL_Color:
                return QString("Color");
                break;
            }
        }
    }
    return QVariant();
}

QVariant MsgDataMappingModel::data(
        const QModelIndex &index,
        int role
        ) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const int row = index.row();
    const int col = index.column();

    const MessageTypeIdentifier &msgType = msgIdentifierStore.at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        switch(col)
        {
        case MsgDataMappingModel::COL_ID:
            return static_cast<QString>(msgType.getID());
            break;
        case MsgDataMappingModel::COL_Code:
            return static_cast<QString>(msgType.getCode());
            break;
        case MsgDataMappingModel::COL_FormatString:
            return
                msgDataMappingStore->getMsgDataMapping(msgType).getMsgDataFormatString();
            break;
        case MsgDataMappingModel::COL_Color:
            return
                msgDataMappingStore->getMsgDataMapping(msgType).getMsgDataDefaultColor();
            break;
        }
        break;
    case Qt::SizeHintRole:
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        return QBrush(
                msgDataMappingStore->getMsgDataMapping(msgType).getMsgDataDefaultColor()
                );
        break;
    case Qt::TextAlignmentRole:
        break;
    case Qt::CheckStateRole:
        break;
    case Qt::UserRole:
        switch(col)
        {
        case MsgDataMappingModel::COL_ID:
            return QVariant::fromValue<MsgIDType>(msgType.getID());
            break;
        case MsgDataMappingModel::COL_Code:
            return QVariant::fromValue<MsgCodeType>(msgType.getCode());
            break;
        case MsgDataMappingModel::COL_FormatString:
            return QVariant::fromValue<QSharedPointer<IMsgDataFormatter>>(
                        msgDataMappingStore->getMsgDataFormatter(msgType)
                    );
            break;
        case MsgDataMappingModel::COL_Color:
            return
                msgDataMappingStore->getMsgDataMapping(msgType).getMsgDataDefaultColor();
            break;
        }
        break;
    }

    return QVariant();
}

Qt::ItemFlags MsgDataMappingModel::flags(
        const QModelIndex &index
        ) const
{
    const int col = index.column();
    Qt::ItemFlags itemFlags = Qt::NoItemFlags;

    switch(col)
    {
        case MsgDataMappingModel::COL_FormatString:
        case MsgDataMappingModel::COL_Color:
            itemFlags |= Qt::ItemIsEditable;
        case MsgDataMappingModel::COL_ID:
        case MsgDataMappingModel::COL_Code:
            itemFlags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    return itemFlags;
}

bool MsgDataMappingModel::setData(
        const QModelIndex &index,
        const QVariant &value,
        int role
        )
{
    const int row = index.row();
    const int col = index.column();
    bool altered = false;

    const MessageTypeIdentifier &msgType = msgIdentifierStore.at(row);
    IMsgDataMapping &msgDataMapping =
            msgDataMappingStore->getMsgDataMapping(msgType);

    switch(role)
    {
    case Qt::EditRole:
        switch(col)
        {
            case MsgDataMappingModel::COL_FormatString:
                msgDataMapping.setMsgDataFormatString(value.value<QString>());
                altered = true;
                break;
            case MsgDataMappingModel::COL_Color:
                msgDataMapping.setMsgDataDefaultColor(value.value<QColor>());
                altered = true;
                break;
        }
        break;
    }

    if(altered)
    {
        emit dataChanged(index, index);
        emit sgnl_MappingHasChanged(msgType.getID(),msgType.getCode());
        return true;
    }
    else
    {
        return false;
    }
}

bool MsgDataMappingModel::removeRows(
        int row,
        int count,
        const QModelIndex &parent
        )
{
    const int modelSize = msgIdentifierStore.size();
    if(!modelSize || ((row+count-1) >= modelSize))
    {
        return false;
    }

    //ToTHINK .. This is definitely for perfomance.. but it is clean

    /* beginRemoveRows(parent, row, row+count-1); */

    int cntr = count;

    while(cntr--)
    {
        msgDataMappingStore->removeMsgDataMapping(
                msgIdentifierStore.at(row+cntr)
                );
    }
    /* msgIdentifierStore.remove(row, count); */

    /* endRemoveRows(); */
    return true;
}


IMsgDataMapping &MsgDataMappingModel::getMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    return msgDataMappingStore->getMsgDataMapping(msgID,msgCode);
}

IMsgDataMapping &MsgDataMappingModel::getMsgDataMapping(
        const MessageTypeIdentifier &msgType
        )
{
    return msgDataMappingStore->getMsgDataMapping(msgType);
}

bool MsgDataMappingModel::contains(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        ) const
{
    return contains(MessageTypeIdentifier(msgID,msgCode));
}

bool MsgDataMappingModel::contains(
        const MessageTypeIdentifier &msgType
        ) const
{
    return msgIdentifierStore.contains(msgType);
}

bool MsgDataMappingModel::contains(
        const IMsgDataMapping &msgDataMapping
        ) const
{
    return contains(msgDataMapping.getMsgID(),msgDataMapping.getMsgCode());
}

void MsgDataMappingModel::appendMsgDataMapping(
        const IMsgDataMapping &msgDataMapping
        )
{
    //DEPRECATED
    msgDataMappingStore->addMsgDataMapping(
            msgDataMapping.getMsgID(),
            msgDataMapping.getMsgCode(),
            msgDataMapping
            );
}

void MsgDataMappingModel::removeMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    removeMsgDataMapping(MessageTypeIdentifier(msgID,msgCode));
}

void MsgDataMappingModel::removeMsgDataMapping(
        const MessageTypeIdentifier &msgType
        )
{
    msgDataMappingStore->removeMsgDataMapping(msgType);
}

void MsgDataMappingModel::clear()
{
    msgDataMappingStore->clear();
}

void MsgDataMappingModel::accept(FileParser *visitor)
{
    msgDataMappingStore->accept(visitor);
}

void MsgDataMappingModel::slt_MsgDataMappingAboutToBeAdded(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    const int currentEndIndex = rowCount();
    beginInsertRows(QModelIndex(),currentEndIndex,currentEndIndex);
}

void MsgDataMappingModel::slt_MsgDataMappingAdded(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    msgIdentifierStore.append(MessageTypeIdentifier(msgID,msgCode));
    endInsertRows();
}

void MsgDataMappingModel::slt_MsgDataMappingAboutToBeRemoved(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    const int index = msgIdentifierStore.indexOf(
            MessageTypeIdentifier(msgID,msgCode)
            );
    beginRemoveRows(QModelIndex(),index,index);
}

void MsgDataMappingModel::slt_MsgDataMappingRemoved(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    msgIdentifierStore.removeAll(MessageTypeIdentifier(msgID,msgCode));
    endRemoveRows();
}

void MsgDataMappingModel::slt_AboutToBeCleared()
{
    beginResetModel();
}

void MsgDataMappingModel::slt_Cleared()
{
    msgIdentifierStore.clear();
    endResetModel();
}

void MsgDataMappingModel::connectToStore()
{
    connect(
            msgDataMappingStore,
            &IMsgDataMappingStore::sgnl_MsgDataMappingAboutToBeAdded,
            this,
            &MsgDataMappingModel::slt_MsgDataMappingAboutToBeAdded
           );

    connect(
            msgDataMappingStore,
            &IMsgDataMappingStore::sgnl_MsgDataMappingAdded,
            this,
            &MsgDataMappingModel::slt_MsgDataMappingAdded
           );

    connect(
            msgDataMappingStore,
            &IMsgDataMappingStore::sgnl_MsgDataMappingAboutToBeRemoved,
            this,
            &MsgDataMappingModel::slt_MsgDataMappingAboutToBeRemoved
           );

    connect(
            msgDataMappingStore,
            &IMsgDataMappingStore::sgnl_MsgDataMappingRemoved,
            this,
            &MsgDataMappingModel::slt_MsgDataMappingRemoved
           );

    connect(
            msgDataMappingStore,
            &IMsgDataMappingStore::sgnl_AboutToBeCleared,
            this,
            &MsgDataMappingModel::slt_AboutToBeCleared
           );

    connect(
            msgDataMappingStore,
            &IMsgDataMappingStore::sgnl_Cleared,
            this,
            &MsgDataMappingModel::slt_Cleared
           );

    connect(
            this,
            &MsgDataMappingModel::sgnl_AddMapping,
            msgDataMappingStore,
            &IMsgDataMappingStore::slt_AddMsgDataMapping
           );

    connect(
            this,
            &MsgDataMappingModel::sgnl_RemoveMapping,
            msgDataMappingStore,
            &IMsgDataMappingStore::slt_RemoveMsgDataMapping
           );

    connect(
            this,
            &MsgDataMappingModel::sgnl_MappingHasChanged,
            msgDataMappingStore,
            &IMsgDataMappingStore::sgnl_MappingHasChanged
           );
}
