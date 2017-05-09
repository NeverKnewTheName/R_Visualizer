#include "MsgCodeDelegate.h"

#include "IMsgCodeMappingManager.h"
#include "MsgCodeMappingModel.h"

#include "MsgCodeLineEdit.h"

#include <QPainter>
#include <QFont>
#include <QFontMetrics>

#include <QLineEdit>
#include <QDebug>

MsgCodeDelegate::MsgCodeDelegate(
        IMsgCodeMappingManager *msgCodeMappingManager,
        QObject *parent
        ) :
    QStyledItemDelegate(parent),
    msgCodeMappingManager(msgCodeMappingManager)
{
    connect(
            msgCodeMappingManager,
            &IMsgCodeMappingManager::sgnl_MsgCodeMappingManagerChanged,
            this,
            &MsgCodeDelegate::slt_MappingHasChanged
           );
}

MsgCodeDelegate::~MsgCodeDelegate()
{
}

void MsgCodeDelegate::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
    const MsgCodeType &msgCode = index.data(Qt::UserRole).value<MsgCodeType>();

    QString alias = msgCodeMappingManager->getAliasToMsgCode(msgCode);

    if(alias.isEmpty())
    {
        alias = static_cast<QString>(msgCode);
    }

    const QColor &colorRep = msgCodeMappingManager->getColorToMsgCode(msgCode);

    painter->save();

    painter->setFont(option.font);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->fillRect(
            option.rect,
            (
                    (option.state & QStyle::State_Selected) ?
                        option.palette.highlight() :
                (option.features & QStyleOptionViewItem::Alternate) ?
                colorRep.darker(100) :
                colorRep
            )
            );

    painter->drawText(
            option.rect,
            Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter,
            alias
            );

    painter->restore();
}

QSize MsgCodeDelegate::sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
    const MsgCodeType &msgCode = index.data(Qt::UserRole).value<MsgCodeType>();

    QString alias = msgCodeMappingManager->getAliasToMsgCode(msgCode);

    if(alias.isEmpty())
    {
        alias = static_cast<QString>(msgCode);
    }

    /* const QStyle *appStyle( QApplication::style() ); */
    QFont font(option.font);

    const QFontMetrics fontMetrics(font);

    return fontMetrics.boundingRect(
                option.rect,
                Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter,
                alias
                ).size();
}

QWidget *MsgCodeDelegate::createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index
        ) const
{
    MsgCodeLineEdit *msgCodeLineEdit = new MsgCodeLineEdit(parent);
    msgCodeLineEdit->setMappingManager(msgCodeMappingManager);

    connect(
            msgCodeLineEdit,
            &MsgCodeLineEdit::sgnl_EditingFinished,
            this,
            &MsgCodeDelegate::slt_CommitAndCloseEditor
           );

    MsgCodeMappingModel *msgCodeMappingModel = new MsgCodeMappingModel(
            msgCodeMappingManager->getStore(),
            qobject_cast<QObject*>(msgCodeLineEdit)
            );
    QCompleter *codeAliasCompleter = new QCompleter(qobject_cast<QObject*>(msgCodeLineEdit));

    codeAliasCompleter->setModel(msgCodeMappingModel);
    codeAliasCompleter->setCompletionColumn(MsgCodeMappingModel::COL_Alias);
    codeAliasCompleter->setCompletionRole(Qt::DisplayRole);
    codeAliasCompleter->setModelSorting(
            QCompleter::CaseInsensitivelySortedModel
            );
    codeAliasCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    msgCodeLineEdit->setCompleter(codeAliasCompleter);


    return msgCodeLineEdit;
}

void MsgCodeDelegate::setEditorData(
        QWidget *editor,
        const QModelIndex &index
        ) const
{
    MsgCodeLineEdit *msgCodeLineEdit = qobject_cast<MsgCodeLineEdit*>(editor);
    if(msgCodeLineEdit)
    {
        msgCodeLineEdit->setMsgCode(index.data(Qt::UserRole).value<MsgCodeType>());
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor,index);
    }
}

void MsgCodeDelegate::setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex &index
        ) const
{
    MsgCodeLineEdit *msgCodeLineEdit = qobject_cast<MsgCodeLineEdit*>(editor);
    if(msgCodeLineEdit)
    {
        const MsgCodeType &msgCodeToSet = msgCodeLineEdit->getMsgCode();

        model->setData(
                index,
                msgCodeToSet,
                Qt::EditRole
                );
    }
    else
    {
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}

void MsgCodeDelegate::slt_MappingHasChanged(
        const IMsgCodeMappingManager &msgCodeMappingManager
        )
{
}

void MsgCodeDelegate::slt_CommitAndCloseEditor()
{
    MsgCodeLineEdit *editor = qobject_cast<MsgCodeLineEdit *>(sender());

    emit commitData(editor);
    emit closeEditor(editor);
}
