#include "MsgIDMappingModel.h"

#include <QBrush>
#include <QString>
#include <QColor>

#include "fileparser.h"

MsgIDMappingModel::MsgIDMappingModel(
        IMsgIDMappingStore *msgIDMappingStore,
        QObject *parent
        ) :
    QAbstractTableModel(parent),
    msgIDMappingStore(msgIDMappingStore)
{
    if(msgIDMappingStore == Q_NULLPTR)
    {
        //ERROR
    }
    QVector<MsgIDType> msgIDs =
            msgIDMappingStore->getContainedMsgIDs();
    if(msgIDs.size())
    {
        beginInsertRows(QModelIndex(),0,msgIDs.size());
        msgIDStore = msgIDs;
        //for(const MsgIDType &msgID : msgIDs)
        //{
            //msgIDStore.append(msgID);
        //}
        endInsertRows();
    }
    connectToStore();
}

MsgIDMappingModel::~MsgIDMappingModel()
{
}

int MsgIDMappingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgIDStore.size();
}

int MsgIDMappingModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return MsgIDMappingModel::COL_NR_OF_COLS;
}

QVariant MsgIDMappingModel::headerData(
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
            case MsgIDMappingModel::COL_ID:
                return QString("ID");
                break;
            case MsgIDMappingModel::COL_Alias:
                return QString("Alias");
                break;
            case MsgIDMappingModel::COL_Color:
                return QString("Color");
                break;
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags MsgIDMappingModel::flags(const QModelIndex &index) const
{
    const int col = index.column();
    Qt::ItemFlags itemFlags = Qt::NoItemFlags;

    switch(col)
    {
        case MsgIDMappingModel::COL_Alias:
        case MsgIDMappingModel::COL_Color:
            itemFlags |= Qt::ItemIsEditable;
        case MsgIDMappingModel::COL_ID:
            itemFlags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    return itemFlags;
}

QVariant MsgIDMappingModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const int row = index.row();
    const int col = index.column();

    const MsgIDType &msgID = msgIDStore.at(row);

    switch(role)
    {
    case Qt::DisplayRole:
        switch(col)
        {
        case MsgIDMappingModel::COL_ID:
            return static_cast<QString>(msgID);
            break;
        case MsgIDMappingModel::COL_Alias:
            return msgIDMappingStore->getAliasToMsgID(msgID);
            break;
        case MsgIDMappingModel::COL_Color:
            return msgIDMappingStore->getColorToMsgID(msgID);
            break;
        }
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        return QBrush(msgIDMappingStore->getColorToMsgID(msgID));
        break;
    case Qt::TextAlignmentRole:
        break;
    case Qt::CheckStateRole:
        break;
    }
    return QVariant();
}

bool MsgIDMappingModel::setData(
        const QModelIndex &index,
        const QVariant &value,
        int role
        )
{
    const int row = index.row();
    const int col = index.column();
    bool altered = false;

    const MsgIDType &msgID = msgIDStore.at(row);
    IMsgIDMapping &msgIDMapping =
        msgIDMappingStore->getMsgIDMappingToMsgID(msgID);

    switch(role)
    {
    case Qt::EditRole:
        switch(col)
        {
            case MsgIDMappingModel::COL_Alias:
                msgIDMapping.setPlainTextAlias(value.value<QString>());
                altered = true;
                break;
            case MsgIDMappingModel::COL_Color:
                msgIDMapping.setColorRepresentation(value.value<QColor>());
                altered = true;
                break;
        }
        break;
    }

    if(altered)
    {
        //ToDO EMIT SIGNALS!!! URGENT!!!
        emit dataChanged(index, index);
        emit sgnl_MappingHasChanged(msgID);
        return true;
    }
    else
    {
        return false;
    }
}

bool MsgIDMappingModel::removeRows(int row, int count, const QModelIndex &parent)
{
    const int modelSize = msgIDStore.size();
    if(!modelSize || ((row+count-1) >= modelSize))
    {
        return false;
    }

    //ToTHINK .. This is definitely for perfomance.. but it is clean

    /* beginRemoveRows(parent, row, row+count-1); */

    int cntr = count;

    while(cntr--)
    {
        msgIDMappingStore->removeMsgIDMapping(msgIDStore.at(row+cntr));
    }
    /* msgIDStore.remove(row, count); */

    /* endRemoveRows(); */
    return true;
}

///////////////////////////////////////

/* IMsgIDMapping &MsgIDMappingModel::getMsgIDMappingToMsgID(const MsgIDType &msgID) const */
/* { */
/*     return msgIDMappingStore->getMsgIDMappingToMsgID(msgID); */
/* } */

IMsgIDMapping &MsgIDMappingModel::getMsgIDMappingToMsgID(const MsgIDType &msgID)
{
    return msgIDMappingStore->getMsgIDMappingToMsgID(msgID);
}

bool MsgIDMappingModel::contains(const MsgIDType &msgID) const
{
    return msgIDStore.contains(msgID);
}

bool MsgIDMappingModel::contains(const IMsgIDMapping &msgIDMapping) const
{
    return msgIDStore.contains(msgIDMapping.getID());
}

//DEPRECATED
void MsgIDMappingModel::appendMsgIDMapping(const IMsgIDMapping &msgIDMappingToAppend)
{
    msgIDMappingStore->addMsgIDMapping(
            msgIDMappingToAppend.getID(),
            msgIDMappingToAppend
            );
    /* const int currentEndIndex = rowCount(); */

    /* beginInsertRows(QModelIndex(), currentEndIndex, currentEndIndex); */
    /* msgIDStore.append(msgIDMappingToAppend.getID()); */
    /* msgIDMappingStore->addMsgIDMapping( */
    /*         msgIDMappingToAppend.getID(), */
    /*         msgIDMappingToAppend */
    /*         ); */
    /* endInsertRows(); */
}

void MsgIDMappingModel::removeMsgIDMapping(const MsgIDType &relatedMsgID)
{
    const int row = msgIDStore.indexOf(relatedMsgID);
    if(!row)
    {
        return;
    }
    removeRows(row, 1, QModelIndex());
}

void MsgIDMappingModel::clear()
{
    beginResetModel();
    msgIDStore.clear();
    msgIDMappingStore->clear();
    endResetModel();
}

void MsgIDMappingModel::accept(FileParser *visitor)
{
    msgIDMappingStore->accept(visitor);
}

void MsgIDMappingModel::slt_MsgIDMappingAboutToBeAdded(
        const MsgIDType &msgID
        )
{
    const int currentEndIndex = rowCount();
    beginInsertRows(QModelIndex(), currentEndIndex, currentEndIndex);
}

void MsgIDMappingModel::slt_MsgIDMappingAdded(
        const MsgIDType &msgID
        )
{
    msgIDStore.append(msgID);
    endInsertRows();
}

void MsgIDMappingModel::slt_MsgIDMappingAboutToBeRemoved(
        const MsgIDType &msgID
        )
{
    //ToTHINK .. This is definitely for perfomance.. but it is clean
    const int index = msgIDStore.indexOf(msgID);
    beginRemoveRows(QModelIndex(), index, index);
}

void MsgIDMappingModel::slt_MsgIDMappingRemoved(
        const MsgIDType &msgID
        )
{
    msgIDStore.removeAll(msgID);
    endRemoveRows();
}

void MsgIDMappingModel::slt_AboutToBeCleared()
{
    beginResetModel();
}

void MsgIDMappingModel::slt_Cleared()
{
    endResetModel();
}

void MsgIDMappingModel::connectToStore()
{
    connect(
            msgIDMappingStore,
            &IMsgIDMappingStore::sgnl_MsgIDMappingAboutToBeAdded,
            this,
            &MsgIDMappingModel::slt_MsgIDMappingAboutToBeAdded
           );

    connect(
            msgIDMappingStore,
            &IMsgIDMappingStore::sgnl_MsgIDMappingAdded,
            this,
            &MsgIDMappingModel::slt_MsgIDMappingAdded
           );

    connect(
            msgIDMappingStore,
            &IMsgIDMappingStore::sgnl_MsgIDMappingAboutToBeRemoved,
            this,
            &MsgIDMappingModel::slt_MsgIDMappingAboutToBeRemoved
           );

    connect(
            msgIDMappingStore,
            &IMsgIDMappingStore::sgnl_MsgIDMappingRemoved,
            this,
            &MsgIDMappingModel::slt_MsgIDMappingRemoved
           );

    connect(
            msgIDMappingStore,
            &IMsgIDMappingStore::sgnl_AboutToBeCleared,
            this,
            &MsgIDMappingModel::slt_AboutToBeCleared
           );

    connect(
            msgIDMappingStore,
            &IMsgIDMappingStore::sgnl_Cleared,
            this,
            &MsgIDMappingModel::slt_Cleared
           );

    connect(
            this,
            &MsgIDMappingModel::sgnl_AddMapping,
            msgIDMappingStore,
            &IMsgIDMappingStore::slt_AddMsgIDMapping
           );

    connect(
            this,
            &MsgIDMappingModel::sgnl_RemoveMapping,
            msgIDMappingStore,
            &IMsgIDMappingStore::slt_RemoveMsgIDMapping
           );

    connect(
            this,
            &MsgIDMappingModel::sgnl_MappingHasChanged,
            msgIDMappingStore,
            &IMsgIDMappingStore::sgnl_MappingHasChanged
           );
}
