#include "MessageStreamWidget.h"
#include "ui_messagestreamwidget.h"

#include <QHeaderView>

#include "IMessageStream.h"
#include "MsgStreamModel.h"

#include <QDebug>

MessageStreamWidget::MessageStreamWidget(
        IMessageStream *msgStream,
        MsgStreamModel *msgStreamModel,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MessageStreamWidget),
    msgStream(msgStream),
    msgStreamModel(msgStreamModel)
{
    init();
    connectToMessageStream();
}

MessageStreamWidget::~MessageStreamWidget()
{
    delete ui;
}

void MessageStreamWidget::init()
{
    ui->setupUi(this);

    ui->msgStreamTableView->setModel(msgStreamModel);
    ui->msgStreamTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QHeaderView *horzHeader = ui->msgStreamTableView->horizontalHeader();

    const int sectionCount = horzHeader->count() - 1;
    const int sectionLength = horzHeader->length() / horzHeader->count();

    for(int i = 0; i < sectionCount; ++i)
    {
        horzHeader->setSectionResizeMode(i,QHeaderView::Interactive);
    }

    horzHeader->setDefaultSectionSize(sectionLength);

    horzHeader->setStretchLastSection(true);

    /* ui->msgStreamTableView->setSelectionMode(
     * QAbstractItemView::ContiguousSelection
     * ); */

    /* //ToDO */
    //ui->codeFilterListView->setItemDelegate(new CodeEditorDelegate(this));

    //ToDO SCROLL TO BOTTOM
}

void MessageStreamWidget::connectToMessageStream()
{
}
