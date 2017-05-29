/**
 * \file msgiddelegate.h
 * \author Christian Neuberger
 * \date 2017-02-06
 * 
 * \brief A Delegate for painting a #Msg's #MsgIDType according to a given #MsgIDRep
 */
#ifndef MSGIDDELEGATE_H
#define MSGIDDELEGATE_H

#include "msgtypemodel.h"
#include "idmodel.h"

#include <QStyledItemDelegate>
#include <QVector>
#include <QPixmap>


/**
 * \brief The #MsgIDDelegate class 
 */
class MsgIDDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a #MsgIDDelegate 
     * 
     * \param[in] idModel The #IDModel that holds all #IDRep that are used in this delegate
     */
    MsgIDDelegate(const IDModel &idModel, QWidget *parent = 0);

    /**
     * \brief Paints a #Msg's #MsgIDType according to its #MsgIDRep
     * 
     * The #Msg's #MsgIDType is queried in the #MsgIDDelegate's #IDModel.
     * If no mapping is found, a default represenation is painted. 
     * Else if a mapping is found, the ID is painted according to the
     * #IDRep's mappings using the provided painter.
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    /**
     * \brief Returns the size hint for the given index with the given option
     */
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
    /**
     * \brief Creates an editor that can be used to edit the ID of a #Msg
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
     * \brief The #IDModel that is queried for #IDReps
     */
    const IDModel &idModel;
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
