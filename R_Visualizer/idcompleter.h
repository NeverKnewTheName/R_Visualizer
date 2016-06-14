#ifndef IDCOMPLETER_H
#define IDCOMPLETER_H

#include <QAbstractListModel>
#include <QCompleter>
#include <QStringList>

class IDCompleter : public QAbstractListModel
{
public:
    IDCompleter(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    QCompleter *getCompleter() const;

private:
    QStringList names;
    QCompleter *completer;

private slots:
    void addIDName(QString &idName);
    void removeIDName(QString &idName);
};

#endif // IDCOMPLETER_H
