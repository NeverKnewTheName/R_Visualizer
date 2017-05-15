#include "MsgCodeMappingEditorDelegate.h"

#include "MsgCodeMappingModel.h"

#include <QLineEdit>
#include <QColorDialog>

MsgCodeMappingEditorDelegate::MsgCodeMappingEditorDelegate(
        QObject *parent
        ) :
    QItemDelegate(parent)
{

}

QWidget *MsgCodeMappingEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgCodeMappingModel::COL_Alias:
    {
        QLineEdit *aliasLineEdit = new QLineEdit(parent);
        connect(
                aliasLineEdit,
                &QLineEdit::editingFinished,
                this,
                &MsgCodeMappingEditorDelegate::commitAndCloseEditor
                );
        return aliasLineEdit;
    }
        break;
    case MsgCodeMappingModel::COL_Color:
    {
        QColorDialog *colorPicker = new QColorDialog(parent);
        connect(
                colorPicker,
                &QColorDialog::finished,
                this,
                &MsgCodeMappingEditorDelegate::commitAndCloseEditor
                );
        return colorPicker;
    }
        break;
    default:
        return QItemDelegate::createEditor(parent,option,index);
    }
}

void MsgCodeMappingEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgCodeMappingModel::COL_Alias:
        qobject_cast<QLineEdit*>(editor)->setText(index.data().toString());
        break;
    case MsgCodeMappingModel::COL_Color:
        qobject_cast<QColorDialog*>(editor)->setCurrentColor(index.data().value<QColor>());
        break;
    default:
        QItemDelegate::setEditorData(editor,index);
    }
}

void MsgCodeMappingEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgCodeMappingModel::COL_Alias:
    {
        QLineEdit *aliasLineEdit = qobject_cast<QLineEdit*>(editor);
        model->setData(index, aliasLineEdit->text(),Qt::EditRole);
    }
        break;
    case MsgCodeMappingModel::COL_Color:
    {
        QColorDialog *colorPicker = qobject_cast<QColorDialog*>(editor);
        model->setData(index, QVariant::fromValue<QColor>(colorPicker->selectedColor()),Qt::EditRole);
    }
        break;
    default:
        QItemDelegate::setModelData(editor,model,index);
    }
}

void MsgCodeMappingEditorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::updateEditorGeometry(editor,option,index);
}

void MsgCodeMappingEditorDelegate::commitAndCloseEditor()
{
    QWidget *editor = qobject_cast<QWidget *>(sender());

    emit commitData(editor);
    emit closeEditor(editor);
}
