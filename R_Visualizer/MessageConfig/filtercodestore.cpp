#include "filtercodestore.h"

#include <QBrush>
#include <QDebug>

FilterCodeStore::FilterCodeStore(MsgTypeModel *msgTypeModel, QObject *parent) : QAbstractListModel(parent), msgTypeModel(msgTypeModel)
{

}


int FilterCodeStore::rowCount(const QModelIndex &parent) const
{
    return codeStore.size();
}

QVariant FilterCodeStore::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    switch(role)
    {
    case Qt::DisplayRole:
    {
        return codeStore.at(row);
//        unsigned int code = codeStore.at(row);
//        QString codeName = msgTypeModel->getNameToCode(code);
//        if(codeName.isEmpty())
//            return QString("0x%1").arg(code/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/); // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
//        else
//            return codeName;
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
//    {
//        QBrush bgBrush(msgTypeModel->getColorToCode(codeStore.at(row)));
//        return bgBrush;
//    }
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

QVariant FilterCodeStore::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
                return QString("Code/Name");
        }
    }
    return QVariant();
}

bool FilterCodeStore::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    switch(role)
    {
    case Qt::EditRole:
//        QString editorContent = value.value<QString>();
//        qDebug() << "FilterCodeStore::setData --- editor content:" << editorContent;
//        bool conversionOK;
//        unsigned int retrievedCode = editorContent.toInt(&conversionOK, (editorContent.startsWith("0x")) ? 16 : 0);

//        if(!conversionOK)
//        {
//            qDebug() << "conversion failed; attempt to retrieve code via name";
//            retrievedCode = msgTypeModel->getCodeToName(editorContent);
//        }
//        codeStore[row] = retrievedCode;

        codeStore[row] = value.value<unsigned int>();
        emit internalModelChanged();
        return true;
        break;
    }
    return false;
}

Qt::ItemFlags FilterCodeStore::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool FilterCodeStore::removeRows(int row, int count, const QModelIndex &parent)
{
    int modelSize = codeStore.size();
    if(modelSize || ((row+count) < modelSize))
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

void FilterCodeStore::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    codeStore.remove(row);
    endRemoveRows();
}

void FilterCodeStore::addCode(unsigned int code)
{
    beginInsertRows(QModelIndex(), codeStore.size(), codeStore.size());
    codeStore.append(code);
    endInsertRows();
    tempIndex = this->index(codeStore.size()-1);
    qDebug() << "Code:" << tempIndex.row();
    emit rowAdded(tempIndex);
}

void FilterCodeStore::addCode(QString &codeString)
{
    beginInsertRows(QModelIndex(), codeStore.size(), codeStore.size());
    codeStore.append(codeString.toUInt());
    endInsertRows();
    tempIndex = this->index(codeStore.size()-1);
    qDebug() << "Code:" << tempIndex.row();
    emit rowAdded(tempIndex);
}

void FilterCodeStore::removeCode(QModelIndex &index)
{
    beginRemoveRows(QModelIndex(),index.row(), index.row());
    codeStore.remove(index.row());
    endRemoveRows();
    emit internalModelChanged();
}

bool FilterCodeStore::containsCode(unsigned int code)
{
    return codeStore.contains(code);
}
