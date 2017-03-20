#include "MsgIDMappingModel.h"

#include "fileparser.h"

MsgIDMappingModel::MsgIDMappingModel(
        IMsgIDMappingStore *msgIDMappingStore,
        QObject *parent
        ) :
    QAbstractTableModel(parent),
    msgIDMappingStore(msgIDMappingStore)
{
}

MsgIDMappingModel::~MsgIDMappingModel()
{
}

int MsgIDMappingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return MsgIDMappingModel::COL_NR_OF_COLS;
}

int MsgIDMappingModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return msgIDStore.size();
}

QVariant MsgIDMappingModel::headerData(int section, Qt::Orientation, int role) const
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
    int col = index.column();

    switch(col)
    {
        case MsgIDMappingModel::COL_ID:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
            break;
        case MsgIDMappingModel::COL_Alias:
        case MsgIDMappingModel::COL_Color:
            return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
            break;
    }

    return Qt::NoItemFlags;
}

QVariant MsgIDMappingModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const int row = index.row();
    const int col = index.column();

    const IMsgIDRep &msgIdRepAtIndex =
        msgIDMappingStore->value(msgIdStore.at(row));

    switch(role)
    {
    case Qt::DisplayRole:
        switch(col)
        {
        case MsgIDMappingModel::COL_ID:
            return QString("0x%1")
                .arg(idRepAtIndex.getID(), 4, 16, QLatin1Char( '0' ));
            break;
        case MsgIDMappingModel::COL_Alias:
            return idRepAtIndex.getPlainTextAlias();
            break;
        case MsgIDMappingModel::COL_Color:
            return idRepAtIndex.getColorRepresentation().name();
            break;
        }
        break;
    case Qt::FontRole:
        break;
    case Qt::BackgroundRole:
        return QBrush(idRepAtIndex.getColorRepresentation());
        break;
    case Qt::TextAlignmentRole:
        break;
    case Qt::CheckStateRole:
        break;
    }
    return QVariant();
}

bool MsgIDMappingModel::setData(const QModelIndex &index, const QVariant &value,
        int role)
{
    const int row = index.row();
    const int col = index.column();
    bool dataChanged = false;

    IMsgIDRep &msgIDRep =
        msgIDMappingStore->getMsgIDRepToMsgID(msgIDStore.at(row));

    switch(role)
    {
    case Qt::EditRole:
        switch(col)
        {
            case MsgIDMappingModel::COL_Alias:
                msgIDRep.setName(value.value<QString>());
                dataChanged = true;
                break;
            case MsgIDMappingModel::COL_Color:
                msgIDRep.setColor(value.value<QColor>());
                dataChanged = true;
                break;
        }
        break;
    }

    if(dataChanged)
    {
        emit dataChanged(index, index);
        emit sgnl_IDRepUpdated(msgIDRep);
        return true;
    }
    else
    {
        return false;
    }
}

/* bool MsgIDMappingModel::insertRows(int row, int count, const QModelIndex &parent) */
/* { */
/*     beginInsertRows(parent, row, row+count-1); */
/*     msgIDStore.insert(row */
/*     endInsertRows(); */
/* } */

bool MsgIDMappingModel::removeRows(int row, int count, const QModelIndex &parent)
{
    const int modelSize = msgIdStore.size();
    if(modelSize || ((row+count-1) < modelSize))
    {
        return false;
    }

    beginRemoveRows(parent, row, row+count-1);

        while(count--)
        {
            msgIDMappingStore->removeMsgIDMapping(msgIDStore.at(row+count));
            msgIDStore.remove(row+count);
        }
    endRemoveRows();
    return true;
}

void MsgIDMappingModel::removeRow(int row, const QModelIndex &parent)
{
    //DEPRECATED!
}


///////////////////////////////////////

IMsgIDRep &MsgIDMappingModel::getMsgIDRepToMsgID(const MsgIDType msgID) const
{
    return msgIDMappingStore->getMsgIDRepToMsgID(msgID);
}

IMsgIDRep &MsgIDMappingModel::getMsgIDRepToMsgID(const MsgIDType msgID)
{
    return msgIDMappingStore->getMsgIDRepToMsgID(msgID);
}

MsgIDMappingModel::contains(const MsgIDType msgID) const
{
    return msgIDStore.contains(msgID);
}

MsgIDMappingModel::contains(const IMsgIDRep &msgIDRep) const
{
    return msgIDStore.contains(msgIDRep.getID());
}

MsgIDMappingModel::appendMsgIDMapping(const IMsgIDRep &msgIDRepToAppend)
{
    const int currentEndIndex = rowCount();

    beginInsertRows(QModelIndex(), currentEndIndex, currentEndIndex);
    msgIDStore.append(msgIDRepToAppend.getID());
    msgIDMappingStore->addMsgIDMapping(msgIDRepToAppend);
    endInsertRows();
}

MsgIDMappingModel::removeMsgIDMapping(const MsgIDType relatedMsgID)
{
    const int row = msgIDStore.indexOf(relatedMsgID);
    if(!row)
    {
        return;
    }
    removeRows(row, 1, QModelIndex());
}

MsgIDMappingModel::clear()
{
    beginResetModel();
    msgIDStore.clear();
    msgIDMappingStore->clear();
    endResetModel();
}

MsgIDMappingModel::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

