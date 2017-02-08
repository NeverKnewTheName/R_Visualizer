#include "filteriddelegate.h"

#include <QLineEdit>
#include <QCompleter>
#include <QPainter>

#include <QDebug>

FilterIDDelegate::FilterIDDelegate(IDModel *idModel, QWidget *parent) :
    QStyledItemDelegate(parent),
    idModel(idModel)
{
    this->availableIDNames.append(QString("Master"));
    this->availableIDNames.append(QString("MastersMaster"));
    this->availableIDNames.append(QString("RablRabl"));
}

void FilterIDDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    QColor background = option.palette.color(
                option.palette.currentColorGroup(),
                (option.features & QStyleOptionViewItem::Alternate) ? QPalette::AlternateBase : QPalette::Base);

    int id = index.data(Qt::DisplayRole).value<int>();
    QColor itemBackground(this->idModel->getColorToID(id));
    if(itemBackground.isValid())
    {
        if(option.features & QStyleOptionViewItem::Alternate)
        {
            background = itemBackground.darker(110);
        }
        else
        {
            background = itemBackground;
        }
    }

    if(option.state & QStyle::State_Selected)
    {
        background = option.palette.color(option.palette.currentColorGroup(), QPalette::Highlight);
    }
    painter->fillRect(option.rect, background);


    QString name = this->idModel->getNameToID(id);
    if(name.isEmpty())
    {
        // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
        name =  QString("0x%1").arg(id/*decimal*/, 4/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/);
    }

    painter->drawText(option.rect, Qt::AlignLeft/* | Qt::AlignBottom*/, name);
}

QSize FilterIDDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *FilterIDDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();
    if (col == 0)
    {
        //NAME
        QLineEdit *textEdit = new QLineEdit(parent);

        QCompleter *completer = new QCompleter(idModel->getAllIDNames(), textEdit);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        textEdit->setCompleter(completer);

        connect(textEdit, &QLineEdit::editingFinished,
                this, &FilterIDDelegate::commitAndCloseEditor);
        return textEdit;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void FilterIDDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();
    if (col == 0) {
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        if(editor == Q_NULLPTR)
        {
            //FAILURE! WHO DID CALL THIS FUNCTION???
            return;
        }
        textEdit->setText(index.data(Qt::DisplayRole).value<QString>());
    }
    else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void FilterIDDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();
    if (col == 0) {
        //NAME
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        QString editorContent = textEdit->text();
        bool conversionOK;
        unsigned int retrievedID = editorContent.toInt(&conversionOK, (editorContent.startsWith("0x")) ? 16 : 0);

        if(!conversionOK)
        {
            retrievedID = idModel->getIDToName(editorContent);
        }
        model->setData(index, retrievedID);
    }
    else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void FilterIDDelegate::commitAndCloseEditor()
{
    QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
    if(editor == Q_NULLPTR)
    {
        //FAILURE! WHO DID SIGNAL THIS SLOT???
        return;
    }
    emit commitData(editor);
    emit closeEditor(editor);
}

void FilterIDDelegate::addIDName(QString &idName)
{
    this->availableIDNames.append(idName);
}

void FilterIDDelegate::removeIDName(QString &idName)
{
    this->availableIDNames.removeAll(idName);
}
