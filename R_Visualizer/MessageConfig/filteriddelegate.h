#ifndef FILTERIDDELEGATE_H
#define FILTERIDDELEGATE_H

#include "idmodel.h"

#include <QStyledItemDelegate>
#include <QStringList>


class FilterIDDelegate : public QStyledItemDelegate
{
public:
    FilterIDDelegate(IDModel *idModel, QWidget *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    IDModel *idModel;
    QStringList availableIDNames;

private slots:
    void commitAndCloseEditor();
    void addIDName(QString &idName);
    void removeIDName(QString &idName);
};

#endif // FILTERIDDELEGATE_H
