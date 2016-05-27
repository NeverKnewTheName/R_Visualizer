#include "msgiddelegate.h"

#include <QPainter>

msgIDDelegate::msgIDDelegate(IDModel *idModel, QWidget *parent)
    : idModel(idModel), QStyledItemDelegate(parent)
{

}

void msgIDDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    int id = index.model()->data(index, Qt::DisplayRole).value<int>();
    QColor background(this->idModel->getColorToID(id));

    if(option.state & QStyle::State_Selected)
    {
        background.darker();
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

QSize msgIDDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *msgIDDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void msgIDDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void msgIDDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void msgIDDelegate::setIDModel(IDModel *idModel)
{
    this->idModel = idModel;
}

void msgIDDelegate::commitAndClsoeEditor()
{

}
