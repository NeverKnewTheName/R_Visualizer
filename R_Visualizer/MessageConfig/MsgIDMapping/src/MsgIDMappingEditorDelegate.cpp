#include "MsgIDMappingEditorDelegate.h"

#include "MsgIDMappingModel.h"

#include <QLineEdit>
#include <QColorDialog>

MsgIDMappingEditorDelegate::MsgIDMappingEditorDelegate(QObject *parent) :
    QItemDelegate(parent)
{

}


QWidget *MsgIDMappingEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgIDMappingModel::COL_Alias:
    {
        QLineEdit *aliasLineEdit = new QLineEdit(parent);
        connect(
                aliasLineEdit,
                &QLineEdit::editingFinished,
                this,
                &MsgIDMappingEditorDelegate::commitAndCloseEditor
                );
        return aliasLineEdit;
    }
        break;
    case MsgIDMappingModel::COL_Color:
    {
        QColorDialog *colorPicker = new QColorDialog(parent);
        connect(
                colorPicker,
                &QColorDialog::finished,
                this,
                &MsgIDMappingEditorDelegate::commitAndCloseEditor
                );
        return colorPicker;
    }
        break;
    default:
        return QItemDelegate::createEditor(parent,option,index);
    }
}

void MsgIDMappingEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgIDMappingModel::COL_Alias:
        qobject_cast<QLineEdit*>(editor)->setText(index.data().toString());
        break;
    case MsgIDMappingModel::COL_Color:
        qobject_cast<QColorDialog*>(editor)->setCurrentColor(index.data().value<QColor>());
        break;
    default:
        QItemDelegate::setEditorData(editor,index);
    }
}

void MsgIDMappingEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgIDMappingModel::COL_Alias:
    {
        QLineEdit *aliasLineEdit = qobject_cast<QLineEdit*>(editor);
        model->setData(index, aliasLineEdit->text(),Qt::EditRole);
    }
        break;
    case MsgIDMappingModel::COL_Color:
    {
        QColorDialog *colorPicker = qobject_cast<QColorDialog*>(editor);
        model->setData(index, QVariant::fromValue<QColor>(colorPicker->selectedColor()),Qt::EditRole);
    }
        break;
    default:
        QItemDelegate::setModelData(editor,model,index);
    }
}

void MsgIDMappingEditorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::updateEditorGeometry(editor,option,index);
}

void MsgIDMappingEditorDelegate::commitAndCloseEditor()
{
    QWidget *editor = qobject_cast<QWidget *>(sender());

    emit commitData(editor);
    emit closeEditor(editor);
}
