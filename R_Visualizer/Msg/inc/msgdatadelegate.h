#ifndef MSGDATADELEGATE_H
#define MSGDATADELEGATE_H

#include "msgtypemodel.h"

#include <QStyledItemDelegate>
#include <QVector>
#include <QPixmap>

class MsgDataDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    MsgDataDelegate(MsgTypeModel &msgTypeModel, QWidget *parent = 0);

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
    MsgTypeModel &msgTypeModel;
    QVector<QPixmap> MsgDataPixMapStore;
    friend class MainWindow;
    int relatedColumnWidth;
    int relatedColumnHeight;

signals:
    void MustUpdatePixmapForIndex(const QStyleOptionViewItem &option, const QModelIndex &index);
    void RowSizeChanged(const int row) const;

private slots:
    void commitAndCloseEditor();
    void UpdatePixmap(const QModelIndex &index);
    void columWidthChanged(int newWidth);
    void columHeightChanged(int newHeight);
};

#endif // MSGDATADELEGATE_H
