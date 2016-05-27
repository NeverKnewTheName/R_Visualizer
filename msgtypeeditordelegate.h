#ifndef MSGTYPEEDITORDELEGATE_H
#define MSGTYPEEDITORDELEGATE_H

#include <QStyledItemDelegate>

class MsgTypeEditorDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    MsgTypeEditorDelegate(QWidget *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

private slots:
    void commitAndCloseEditor();
};

#endif // MSGTYPEEDITORDELEGATE_H
