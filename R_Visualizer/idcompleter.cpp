#include "idcompleter.h"

IDCompleter::IDCompleter(QObject *parent) :
    QAbstractListModel(parent),
    completer(new QCompleter(parent))
{
    completer->setModel(this);
    completer->setCompletionRole(Qt::DisplayRole);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    names.append(QString("Master"));
    names.append(QString("RablRabl"));
    names.append(QString("MastersMaster"));
}

int IDCompleter::rowCount(const QModelIndex &parent) const
{
    return names.size();
}

QVariant IDCompleter::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    switch(role)
    {
    case Qt::DisplayRole:
        return names.at(row);
        break;
    }
    return QVariant();
}

QCompleter *IDCompleter::getCompleter() const
{
    return completer;
}

void IDCompleter::addIDName(QString &idName)
{
    names.append(idName);
}

void IDCompleter::removeIDName(QString &idName)
{
    names.removeAll(idName);
}
