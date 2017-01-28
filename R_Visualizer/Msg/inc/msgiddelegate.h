#ifndef MSGIDDELEGATE_H
#define MSGIDDELEGATE_H

#include "msgtypemodel.h"
#include "idmodel.h"

#include <QStyledItemDelegate>
#include <QVector>
#include <QPixmap>


class MsgIDDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    MsgIDDelegate(IDModel &idModel, QWidget *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    IDModel &idModel;
    QVector<QPixmap> MsgIDPixMapStore;
    friend class MainWindow;
    int relatedColumnWidth;
    int relatedColumnHeight;

private slots:
    void commitAndCloseEditor();
    void UpdatePixmap(const QModelIndex &index);
    void columWidthChanged(int newWidth);
    void columHeightChanged(int newHeight);
};

#endif // MSGIDDELEGATE_H
