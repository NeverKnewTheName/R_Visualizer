#include "MsgCodeMappingModel.h"

#include <QBrush>
#include <QString>
#include <QColor>

#include "fileparser.h"

MsgCodeMappingModel::MsgCodeMappingModel(
        IMsgCodeMappingStore *msgCodeMappingStore,
        QObject *parent
        ) :
    QAbstractTableModel(parent),
    msgCodeMappingStore(msgCodeMappingStore)
{
    if(msgCodeMappingStore == Q_NULLPTR)
    {
        //ERROR
    }
    QVector<MsgCodeType> msgCodes =
            msgCodeMappingStore->getContainedMsgCodes();
    if(msgCodes.size())
    {
        beginInsertRows(QModelIndex(),0,msgCodes.size());
        msgCodeStore = msgCodes;
        //for(const MsgCodeType &msgCode : msgCodes)
        //{
            //msgCodeStore.append(msgCode);
        //}
        endInsertRows();
    }
    connectToStore();
}

MsgCodeMappingModel::~MsgCodeMappingModel()
{
}

int MsgCodeMappingModel::rowCount(
        const QModelIndex &parent
        ) const
{
    Q_UNUSED(parent)
    return msgCodeStore.size();
}

int MsgCodeMappingModel::columnCount(
        const QModelIndex &parent
        ) const
{
    Q_UNUSED(parent)
    return MsgCodeMappingModel::COL_NR_OF_COLS;
}

QVariant MsgCodeMappingModel::headerData(
        int section,
        Qt::Orientation orientation,
        int role
        ) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
                case MsgCodeMappingModel::COL_Code:
                    return QString("Code");
                    break;
                case MsgCodeMappingModel::COL_Alias:
                    return QString("Alias");
                    break;
                case MsgCodeMappingModel::COL_Color:
                    return QString("Color");
                    break;
            }
        }
    }
    return QVariant();
}

QVariant MsgCodeMappingModel::data(
        const QModelIndex &index,
        int role
        ) const
{
    const int row = index.row();
    const int col = index.column();

    const MsgCodeType &msgCode = msgCodeStore.at(row);

    switch(role)
    {
        case Qt::DisplayRole:
            switch(col)
            {
                case MsgCodeMappingModel::COL_Code:
                    return static_cast<QString>(msgCode);
                    break;
                case MsgCodeMappingModel::COL_Alias:
                    return msgCodeMappingStore->getAliasToMsgCode(msgCode);
                    break;
                case MsgCodeMappingModel::COL_Color:
                    return msgCodeMappingStore->getColorToMsgCode(msgCode);
                    break;
            }
            break;
        case Qt::FontRole:
            break;
        case Qt::BackgroundRole:
            return QBrush(msgCodeMappingStore->getColorToMsgCode(msgCode));
            break;
        case Qt::TextAlignmentRole:
            break;
        case Qt::CheckStateRole:
            break;
        case Qt::UserRole:
            return QVariant::fromValue<MsgCodeType>(msgCode);
            break;
    }
    return QVariant();
}

bool MsgCodeMappingModel::setData(
        const QModelIndex &index,
        const QVariant &value,
        int role
        )
{
    const int row = index.row();
    const int col = index.column();
    bool altered = false;

    const MsgCodeType &msgCode = msgCodeStore.at(row);
    IMsgCodeMapping &msgCodeMapping =
        msgCodeMappingStore->getMsgCodeMappingToMsgCode(msgCode);

    switch(role)
    {
        case Qt::EditRole:
            switch(col)
            {
                case MsgCodeMappingModel::COL_Alias:
                    msgCodeMapping.setPlainTextAlias(
                            value.value<QString>()
                            );
                    break;
                case MsgCodeMappingModel::COL_Color:
                    msgCodeMapping.setColorRepresentation(
                            value.value<QColor>()
                            );
                    break;
            }
            break;
    }

    if(altered)
    {
        emit dataChanged(index,index);
        emit sgnl_MappingHasChanged(msgCode);
        return true;
    }
    else
    {
        return false;
    }
}

bool MsgCodeMappingModel::contains(const MsgCodeType &msgCode) const
{
    return msgCodeStore.contains(msgCode);
}

bool MsgCodeMappingModel::contains(const IMsgCodeMapping &msgCodeMapping) const
{
    return msgCodeStore.contains(msgCodeMapping.getCode());
}

bool MsgCodeMappingModel::removeRows(
        int row,
        int count,
        const QModelIndex &parent
    )
{
    const int modelSize = msgCodeStore.size();
    if(!modelSize || ((row+count-1) >= modelSize))
    {
        return false;
    }

    int cntr = count;

    while(cntr--)
    {
        msgCodeMappingStore->removeMsgCodeMapping(
                msgCodeStore.at(row+cntr)
                );
    }

    return true;
}

Qt::ItemFlags MsgCodeMappingModel::flags(
        const QModelIndex &index
        ) const
{
    const int col = index.column();
    Qt::ItemFlags itemFlags = Qt::NoItemFlags;

    switch(col)
    {
        case MsgCodeMappingModel::COL_Alias:
        case MsgCodeMappingModel::COL_Color:
            itemFlags |= Qt::ItemIsEditable;
        case MsgCodeMappingModel::COL_Code:
            itemFlags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    return itemFlags;
}

IMsgCodeMapping &MsgCodeMappingModel::getMsgCodeMappingToMsgCode(
        const MsgCodeType &msgCode
        )
{
    return msgCodeMappingStore->getMsgCodeMappingToMsgCode(msgCode);
}

void MsgCodeMappingModel::appendMsgCodeMapping(
        const IMsgCodeMapping &msgCodeMappingToAppend
        )
{
    const int currentEndIndex = rowCount();

    beginInsertRows(QModelIndex(), currentEndIndex, currentEndIndex);
    msgCodeStore.append(msgCodeMappingToAppend.getCode());
    msgCodeMappingStore->addMsgCodeMapping(
            msgCodeMappingToAppend.getCode(),
            msgCodeMappingToAppend
            );
    endInsertRows();
}

void MsgCodeMappingModel::removeMsgCodeMapping(
        const MsgCodeType &relatedCode
        )
{
    const int row = msgCodeStore.indexOf(relatedCode);
    if(!row)
    {
        return;
    }
    removeRows(row, 1, QModelIndex());
}

void MsgCodeMappingModel::clear()
{
    beginResetModel();
    msgCodeStore.clear();
    msgCodeMappingStore->clear();
    endResetModel();
}

void MsgCodeMappingModel::accept(FileParser *visitor)
{
    msgCodeMappingStore->accept(visitor);
}

void MsgCodeMappingModel::slt_MsgCodeMappingAboutToBeAdded(
        const MsgCodeType &msgCode
        )
{
    const int currentEndIndex = rowCount();
    beginInsertRows(QModelIndex(), currentEndIndex, currentEndIndex);
}

void MsgCodeMappingModel::slt_MsgCodeMappingAdded(
        const MsgCodeType &msgCode
        )
{
    msgCodeStore.append(msgCode);
    endInsertRows();
}

void MsgCodeMappingModel::slt_MsgCodeMappingAboutToBeRemoved(
        const MsgCodeType &msgCode
        )
{
    const int index = msgCodeStore.indexOf(msgCode);
    beginRemoveRows(QModelIndex(), index, index);
}

void MsgCodeMappingModel::slt_MsgCodeMappingRemoved(
        const MsgCodeType &msgCode
        )
{
    msgCodeStore.removeAll(msgCode);
    endRemoveRows();
}

void MsgCodeMappingModel::slt_AboutToBeCleared()
{
    beginResetModel();
}

void MsgCodeMappingModel::slt_Cleared()
{
    endResetModel();
}

void MsgCodeMappingModel::connectToStore()
{
    connect(
            msgCodeMappingStore,
            &IMsgCodeMappingStore::sgnl_MsgCodeMappingAboutToBeAdded,
            this,
            &MsgCodeMappingModel::slt_MsgCodeMappingAboutToBeAdded
           );

    connect(
            msgCodeMappingStore,
            &IMsgCodeMappingStore::sgnl_MsgCodeMappingAdded,
            this,
            &MsgCodeMappingModel::slt_MsgCodeMappingAdded
           );

    connect(
            msgCodeMappingStore,
            &IMsgCodeMappingStore::sgnl_MsgCodeMappingAboutToBeRemoved,
            this,
            &MsgCodeMappingModel::slt_MsgCodeMappingAboutToBeRemoved
           );

    connect(
            msgCodeMappingStore,
            &IMsgCodeMappingStore::sgnl_MsgCodeMappingRemoved,
            this,
            &MsgCodeMappingModel::slt_MsgCodeMappingRemoved
           );

    connect(
            msgCodeMappingStore,
            &IMsgCodeMappingStore::sgnl_AboutToBeCleared,
            this,
            &MsgCodeMappingModel::slt_AboutToBeCleared
           );

    connect(
            msgCodeMappingStore,
            &IMsgCodeMappingStore::sgnl_Cleared,
            this,
            &MsgCodeMappingModel::slt_Cleared
           );

    connect(
            this,
            &MsgCodeMappingModel::sgnl_AddMapping,
            msgCodeMappingStore,
            &IMsgCodeMappingStore::slt_AddMsgCodeMapping
           );

    connect(
            this,
            &MsgCodeMappingModel::sgnl_RemoveMapping,
            msgCodeMappingStore,
            &IMsgCodeMappingStore::slt_RemoveMsgCodeMapping
           );

    connect(
            this,
            &MsgCodeMappingModel::sgnl_MappingHasChanged,
            msgCodeMappingStore,
            &IMsgCodeMappingStore::sgnl_MappingHasChanged
           );
}
