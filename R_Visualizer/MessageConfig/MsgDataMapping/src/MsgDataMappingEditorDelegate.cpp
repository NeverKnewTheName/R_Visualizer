#include "MsgDataMappingEditorDelegate.h"

#include "MsgDataMappingModel.h"

#include "MsgDataFormatStringEditorDialog.h"

#include <QLineEdit>
#include <QColorDialog>

MsgDataMappingEditorDelegate::MsgDataMappingEditorDelegate(QObject *parent) :
    QItemDelegate(parent)
{

}


QWidget *MsgDataMappingEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgDataMappingModel::COL_FormatString:
    {
        MsgDataFormatStringEditorDialog *formatStringEditor =
                new MsgDataFormatStringEditorDialog(parent);
        connect(
                formatStringEditor,
                &MsgDataFormatStringEditorDialog::accepted,
                this,
                &MsgDataMappingEditorDelegate::commitAndCloseEditor
                );
        return formatStringEditor;
    }
        break;
    case MsgDataMappingModel::COL_Color:
    {
        QColorDialog *colorPicker = new QColorDialog(parent);
        connect(
                colorPicker,
                &QColorDialog::finished,
                this,
                &MsgDataMappingEditorDelegate::commitAndCloseEditor
                );
        return colorPicker;
    }
        break;
    default:
        return QItemDelegate::createEditor(parent,option,index);
    }
}

void MsgDataMappingEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgDataMappingModel::COL_FormatString:
        qobject_cast<MsgDataFormatStringEditorDialog*>(editor)
                ->setFormatString(index.data().toString());
        break;
    case MsgDataMappingModel::COL_Color:
        qobject_cast<QColorDialog*>(editor)->setCurrentColor(index.data().value<QColor>());
        break;
    default:
        QItemDelegate::setEditorData(editor,index);
    }
}

void MsgDataMappingEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgDataMappingModel::COL_FormatString:
    {
        MsgDataFormatStringEditorDialog *formatStringEditor =
                qobject_cast<MsgDataFormatStringEditorDialog*>(editor);
        model->setData(index, formatStringEditor->getFormatString(),Qt::EditRole);
    }
        break;
    case MsgDataMappingModel::COL_Color:
    {
        QColorDialog *colorPicker = qobject_cast<QColorDialog*>(editor);
        model->setData(index, QVariant::fromValue<QColor>(colorPicker->selectedColor()),Qt::EditRole);
    }
        break;
    default:
        QItemDelegate::setModelData(editor,model,index);
    }
}

void MsgDataMappingEditorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::updateEditorGeometry(editor,option,index);
}

void MsgDataMappingEditorDelegate::commitAndCloseEditor()
{
    QWidget *editor = qobject_cast<QWidget *>(sender());

    emit commitData(editor);
    emit closeEditor(editor);
}
