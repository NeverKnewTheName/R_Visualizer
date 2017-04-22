#include "msgtypemodel.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <QBrush>
#include <QRegularExpression>

#include <QDebug>

#include "fileparser.h"

MsgTypeModel::MsgTypeModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int MsgTypeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return codeStore.size();
}

int MsgTypeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COL_NR_OF_COLS;
}

QVariant MsgTypeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    int row = index.row();
    int col = index.column();
    const MsgTypeMapping &msgTypeMappingAtIndex = msgTypePropStore.value(codeStore.at(row));

    switch(role)
    {
    case Qt::DisplayRole:
        switch(col)
        {
            case COL_CODE:
                return QString("0x%1")
                    .arg(msgTypeMappingAtIndex.getCode()/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/); 
                // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
                break;
            case COL_CODENAME:
                return msgTypeMappingAtIndex.getCodeName();
                break;
            case COL_MESSAGEFORMAT:
                return msgTypeMappingAtIndex.getMessageFormat();
                break;
            case COL_COLOR:
                return msgTypeMappingAtIndex.getColor().name();
                break;
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
        return QBrush(msgTypeMappingAtIndex.getColor());
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

bool MsgTypeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();
    switch(role)
    {
    case Qt::EditRole:
        if(col == COL_CODENAME) msgTypePropStore[codeStore[row]].setCodeName(value.value<QString>());
        if(col == COL_MESSAGEFORMAT ) msgTypePropStore[codeStore[row]].setMessageFormat(value.value<QString>());
        if(col == COL_COLOR) msgTypePropStore[codeStore[row]].setColor(value.value<QColor>());
        emit dataChanged(index, index);
        emit sgnl_MsgTypeMappingUpdated(msgTypePropStore[codeStore[row]]);
        return true;
        break;
    }
    return false;
}

QVariant MsgTypeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case COL_CODE:
                return QString("Code");
                break;
            case COL_CODENAME:
                return QString("Name");
                break;
            case COL_MESSAGEFORMAT:
                return QString("Message Format");
                break;
            case COL_COLOR:
                return QString("Color");
                break;
            }
        }
    }
    return QVariant();
}

bool MsgTypeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    int modelSize = codeStore.size();
    if(modelSize || ((row+count) < modelSize))
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

void MsgTypeModel::removeRow(int row, const QModelIndex &parent)
{
    const MsgCodeType relatedCode = codeStore.at(row);
    beginRemoveRows(parent, row, row);
    msgTypePropStore.remove(relatedCode);
    codeStore.remove(row);
    endRemoveRows();
    emit sgnl_MsgTypeMappingRemoved(relatedCode);
}

Qt::ItemFlags MsgTypeModel::flags(const QModelIndex &index) const
{
    int col = index.column();

    switch(col)
    {
        case COL_CODE:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
            break;
        case COL_CODENAME:
        case COL_MESSAGEFORMAT:
        case COL_COLOR:
            return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
            break;
    }
    return Qt::NoItemFlags;
}

void MsgTypeModel::add(const MsgTypeMapping &msgTypeMapping)
{
    int newRow = codeStore.size();
    const MsgCodeType code = msgTypeMapping.getCode();
    beginInsertRows(QModelIndex(),newRow,newRow);
    codeStore.append(code);
    msgTypePropStore.remove(code);
    msgTypePropStore.insertMulti(code, msgTypeMapping);
    endInsertRows();
    emit sgnl_MsgTypeMappingAdded(msgTypeMapping);
}

MsgTypeMapping MsgTypeModel::getMsgTypeMappingToCode(const MsgCodeType code) const
{
    if(contains(code))
    {
        return msgTypePropStore.value(code);
    }
    else
    {
        return MsgTypeMapping(code);
    }
}

void MsgTypeModel::clear()
{
    // clearing all data is a reset of the model
    // In order to ease the processing, do not call begin/endRemoveRows
    // call begin/endResetModel instead, which ultimately forces all attached
    // views to reload the model
    beginResetModel();
    msgTypePropStore.clear();
    codeStore.clear();
    endResetModel();
    //    emit internalModelChanged();
}

const int MsgTypeModel::size() const
{
    return codeStore.size();
}

const MsgTypeMapping &MsgTypeModel::at(const int index) const
{
    return msgTypePropStore.value(codeStore.at(index));
}

bool MsgTypeModel::contains(const MsgCodeType MsgCode) const
{
    return msgTypePropStore.contains(MsgCode);
}

QString MsgTypeModel::getNameToCode(const MsgCodeType code) const
{
    if(msgTypePropStore.contains(code))
    {
        return msgTypePropStore[code].getCodeName();
    }
    return QString("");
}

MsgCodeType MsgTypeModel::getCodeToName(const QString &name) const
{
    for( auto &msgTypeMapping : msgTypePropStore )
    {
        if(!name.compare(msgTypeMapping.getCodeName(),Qt::CaseInsensitive))
            return msgTypeMapping.getCode();
    }

    return 0;
}

QString MsgTypeModel::getMessageToCode(const MsgCodeType code) const
{
    if(msgTypePropStore.contains(code))
    {
        return msgTypePropStore[code].getMessageFormat();
    }

    return QString("");
}

QColor MsgTypeModel::getColorToCode(const MsgCodeType code) const
{
    if(msgTypePropStore.contains(code))
    {
        return msgTypePropStore[code].getColor();
    }

    return QColor();
}

int MsgTypeModel::getNrLinesToCode(const MsgCodeType code)
{
    if(msgTypePropStore.contains(code))
    {
        return msgTypePropStore[code].getMessageFormat().count("\n");
    }

    return 1;
}

QStringList MsgTypeModel::getAllCodeNames() const
{
    QStringList names;
    for(const auto &msgTypeMapping : msgTypePropStore )
    {
        names.append(msgTypeMapping.getCodeName());
    }
    return names;
}

QByteArray MsgTypeModel::ParseToJson() const
{
    QJsonArray jsonMsgsArr;
    for(const MsgCodeType &code : codeStore)
    {
        const MsgTypeMapping &newMsgTypeMapping = msgTypePropStore[code];
        jsonMsgsArr.append(newMsgTypeMapping.parseOUT());
    }
    return QJsonDocument(jsonMsgsArr).toJson(QJsonDocument::Indented);
}

void MsgTypeModel::ParseFromJson(const QByteArray &jsonFile)
{
    this->clear();
    QJsonArray jsonMsgsArr = QJsonDocument::fromJson(jsonFile).array();
    for(auto&& item : jsonMsgsArr)
    {
        add(MsgTypeMapping::createObjFromJson(item.toObject()));
    }
}

void MsgTypeModel::paintMsgTypeMapping(QPainter *painter, const QStyleOptionViewItem &option, const MsgCodeType code, Msg &msg) const
{
    msgTypePropStore[code].paintMsgTypeMapping(painter, option, msg);
}

QCompleter *MsgTypeModel::createMsgTypeCompleter(QObject *parent) const
{
    QCompleter *newMsgTypeCompleter = new QCompleter(parent);
    /*
     * Somehow the QCompleter wants a non-const pointer
     * to a model... This does not make sense.. but HEY!
     * I guess that's what's const_cast is for!
     */
    newMsgTypeCompleter->setModel(const_cast<MsgTypeModel*>(this));
    newMsgTypeCompleter->setCompletionColumn(COL_CODENAME);
    newMsgTypeCompleter->setCompletionRole(Qt::DisplayRole);
    newMsgTypeCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    return newMsgTypeCompleter;
}

void MsgTypeModel::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
