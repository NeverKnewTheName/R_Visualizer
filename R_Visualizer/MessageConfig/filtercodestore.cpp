#include "filtercodestore.h"

#include <QBrush>
#include <QDebug>

FilterCodeStore::FilterCodeStore(MsgTypeModel *msgTypeModel, QObject *parent) : QAbstractListModel(parent), msgTypeModel(msgTypeModel)
{

}


int FilterCodeStore::rowCount(const QModelIndex &parent) const
{
    codeStore.size();
}

QVariant FilterCodeStore::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    switch(role)
    {
    case Qt::DisplayRole:
    {
        unsigned int code = codeStore.at(row);
        QString codeName = msgTypeModel->getNameToCode(code);
        if(codeName.isEmpty())
            return QString("0x%1").arg(code/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/); // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
        else
            return codeName;
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
    {
        QBrush bgBrush(msgTypeModel->getColorToCode(codeStore.at(row)));
        return bgBrush;
    }
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

void FilterCodeStore::addCode(unsigned int code)
{
    codeStore.append(code);
}

void FilterCodeStore::addCode(QString &codeString)
{
    codeStore.append(codeString.toUInt());
}

void FilterCodeStore::removeCode(unsigned int code)
{
    codeStore.removeOne(code);
}
