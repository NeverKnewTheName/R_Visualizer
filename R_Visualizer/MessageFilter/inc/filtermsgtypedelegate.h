#ifndef FILTERMSGTYPEDELEGATE_H
#define FILTERMSGTYPEDELEGATE_H

#include "msgtypemodel.h"
#include <QStyledItemDelegate>

class FilterMsgTypeDelegate : public QStyledItemDelegate
{
public:
    FilterMsgTypeDelegate(MsgTypeModel *msgTypeModel, QWidget *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
    MsgTypeModel *msgTypeModel;

private slots:
    void commitAndCloseEditor();
};

#endif // FILTERMSGTYPEDELEGATE_H
