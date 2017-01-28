#include "evaluatortablemodel.h"

EvaluatorTablemodel::EvaluatorTablemodel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant EvaluatorTablemodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section)
        {
        case 0:
            return QString("Type");
            break;
        case 1:
            return QString("Function");
            break;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

int EvaluatorTablemodel::rowCount(const QModelIndex &parent) const
{

    return EvaluatorStore.size();
}

int EvaluatorTablemodel::columnCount(const QModelIndex &parent) const
{

    return 2;
}

QVariant EvaluatorTablemodel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    int col = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
        if(col == 0) return EvaluatorStore.at(row)->printName();
        if(col == 1) return EvaluatorStore.at(row)->printFunction();
        break;
    case Qt::EditRole:
        return QVariant::fromValue(static_cast<void *>(EvaluatorStore.at(row)));
    }
    return QVariant();
}

Qt::ItemFlags EvaluatorTablemodel::flags(const QModelIndex &index) const
{
    return (Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

bool EvaluatorTablemodel::appendRow(TemplateValueEvaluator *EvaluatorToAdd)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    EvaluatorStore.append(EvaluatorToAdd);
    endInsertRows();
    return true;
}

bool EvaluatorTablemodel::updateRow(TemplateValueEvaluator *EvaluatorToAdd)
{
    int index = EvaluatorStore.indexOf(EvaluatorToAdd);
//    modelReset();
}

bool EvaluatorTablemodel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool EvaluatorTablemodel::removeRow(TemplateValueEvaluator *EvaluatorToRemove)
{
    int indexOfEvalToRemove = EvaluatorStore.indexOf(EvaluatorToRemove);
    beginRemoveRows(QModelIndex(), indexOfEvalToRemove, indexOfEvalToRemove);
    EvaluatorStore.removeAt(indexOfEvalToRemove);
    endRemoveRows();
    return true;
}

bool EvaluatorTablemodel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    EvaluatorStore.removeAt(row);
    endRemoveRows();
    return true;
}

bool EvaluatorTablemodel::removeRows(int row, int count, const QModelIndex &parent)
{
    while(count--)
    {
        removeRow(row, parent);
    }
    return true;
}

