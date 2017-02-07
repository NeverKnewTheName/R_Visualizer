/**
 * \file msgdatadelegate.h
 * \author Christian Neuberger
 * \date 2017-02-06
 * 
 * \brief A Delegate for painting a #Msg's #MsgCodeType according to a given #MsgTypeRep
 */
#ifndef MSGDATADELEGATE_H
#define MSGDATADELEGATE_H

#include "msgtypemodel.h"

#include <QStyledItemDelegate>
#include <QVector>
#include <QPixmap>

/**
 * \brief The #MsgDataDelegaten class 
 */
class MsgDataDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a #MsgDataDelegate
     * 
     * \param[in] msgTypeModel THe #MsgTypeModel that holds all #MsgTypeRep that are used in this delegate
     */
    MsgDataDelegate(MsgTypeModel &msgTypeModel, QWidget *parent = 0);

    /**
     * \brief Paints a #Msg's #MsgCodeType and data according to its #MsgTypeRep
     *
     * The #Msg's #MsgCodeType is queried in the #MsgDataDelegate's #MsgTypeModel.
     * If no mapping is found, a default representation is painted.
     * Else if a mapping is found, the code and data are painted according to the
     * #MsgTypeRep's mappings using the provided painter.
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    /**
     * \brief Retunrs the size hint for the given index with the given option
     */
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
    /**
     * \brief Creates an editor that can be used to edit the code and data of a #Msg
     */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    /**
     * \brief Sets the editor's data fields that was previously created with #createEditor
     */
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    /**
     * \brief Sets the underlying model's data for the given index to the contents of the given editor
     */
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    /**
     * \brief The #MsgTypeModel that is queried for #MsgTypeReps
     */
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
