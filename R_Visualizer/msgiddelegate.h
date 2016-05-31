#ifndef MSGIDDELEGATE_H
#define MSGIDDELEGATE_H

/*
 * DEPRECATED
 */


#include "idmodel.h"
#include <QStyledItemDelegate>

class msgIDDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    msgIDDelegate(IDModel *idModel, QWidget *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setIDModel(IDModel *idModel);

private:
    IDModel *idModel;

private slots:
    void commitAndClsoeEditor();
};

#endif // MSGIDDELEGATE_H
