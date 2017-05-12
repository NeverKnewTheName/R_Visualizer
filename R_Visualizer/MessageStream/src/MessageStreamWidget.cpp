#include "MessageStreamWidget.h"
#include "ui_messagestreamwidget.h"

#include <QHeaderView>

#include "IMessageStream.h"
#include "MsgStreamModel.h"

#include <QFileDialog>
#include <QString>

#include <QScrollBar>

#include <QDebug>

#include "csvinparser.h"
#include "csvoutparser.h"
#include "jsoninparser.h"
#include "jsonoutparser.h"

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
    ui->followUpCheckBox->setChecked(msgStream->getContinuousFlag());
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
    ui->msgStreamTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->msgStreamTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    //ui->msgStreamTableView->setFocusPolicy(Qt::NoFocus);
    ui->msgStreamTableView->setAlternatingRowColors(true);

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
    QScrollBar *horzScrollBar = ui->msgStreamTableView->verticalScrollBar();

    connect(
            horzScrollBar,
            &QScrollBar::valueChanged,
                [=](int value){
                    if(value)
                    {
                        const int scrollBarMax = horzScrollBar->maximum();
                        if(value == scrollBarMax)
                        {
                            //Value BOTTOM reached
                            qDebug() << "Scroll to Bottom Detected";
                            bool selectionRestore = false;
                            QItemSelectionModel *selectionModel = ui->msgStreamTableView->selectionModel();
                            if(selectionModel->selectedRows().size())
                            {
                                selectionRestore = true;
                                selectionModel->clearSelection();
                            }
                            if(msgStream->fetchNext())
                            {
                                if(selectionRestore)
                                {
                                    const int rowCount = ui->msgStreamTableView->model()->rowCount();
                                    selectionModel->select(ui->msgStreamTableView->model()->index(rowCount-3,0),QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                                }
                                horzScrollBar->setSliderPosition(scrollBarMax-horzScrollBar->singleStep());
                            }
                        }
                    }
                    else
                    {
                        //Value TOP reached
                        qDebug() << "Scroll to Top Detected";
                        bool selectionRestore = false;
                        QItemSelectionModel *selectionModel = ui->msgStreamTableView->selectionModel();
                        if(selectionModel->selectedRows().size())
                        {
                            selectionRestore = true;
                            selectionModel->clearSelection();
                        }
                        if(msgStream->fetchPrevious())
                        {
                            if(selectionRestore)
                            {
                                selectionModel->select(ui->msgStreamTableView->model()->index(2,0),QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                            }
                            horzScrollBar->setSliderPosition(horzScrollBar->singleStep());
                        }
                    }

                }
            );
    //connect(
            //horzScrollBar,
            //&QScrollBar::actionTriggered,
                //[=](int action){
                    //switch(action)
                    //{
                    //case QScrollBar::SliderSingleStepAdd:
                        //qDebug() << "SliderSingleStepAdd";
                        //break;
                    //case QScrollBar::SliderSingleStepSub:
                        //qDebug() << "SliderSingleStepSub";
                        //break;
                    //case QScrollBar::SliderPageStepAdd:
                        //qDebug() << "SliderPageStepAdd";
                        //break;
                    //case QScrollBar::SliderPageStepSub:
                        //qDebug() << "SliderPageStepSub";
                        //break;
                    //case QScrollBar::SliderToMaximum:
                        //qDebug() << "SliderToMaximum";
                        //break;
                    //case QScrollBar::SliderToMinimum:
                        //qDebug() << "SliderToMinimum";
                        //break;
                    //default:
                        //qDebug() << "Action: " << action;
                    //}
                //}
            //);
}

void MessageStreamWidget::on_loadBtn_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(
            this,
            QString("Open"),
            QString(),
            "JSON File (*.json)"
            );
    qDebug() << openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    else
    {
        msgStream->clear();
        //ToDO
        // read file content
        JsonInParser jsonInParser;
        jsonInParser.setJsonDocument(
                QJsonDocument::fromJson(jsonOpenFile.readAll())
                );
        msgStream->accept(&jsonInParser);
        /* idModel.ParseFromJson(jsonOpenFile.readAll());
         * //ToDO check for error (-1) */
        // parse file
        // populate ui
    }
    // close file
    jsonOpenFile.close();
}

void MessageStreamWidget::on_storeBtn_clicked()
{
    QString saveLoc = QFileDialog::getSaveFileName(
            this,
            QString("Save as"),
            QString(),
            "JSON File (*.json)"
            );
    qDebug() << saveLoc;
    QFile jsonSaveFile(saveLoc);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    } else
    {
        //ToDO
        // extract ui content
        // parse content to file format
        // write to file
        JsonOutParser jsonOutParser;
        msgStream->accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson());
        //ToDO check for error (-1)
    }
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MessageStreamWidget::on_scrollTopBtn_clicked()
{
    //const bool success = msgStream->fetchPrevious();
    //qDebug() << __PRETTY_FUNCTION__ << " -- " << success;
    msgStream->fetchTop();
    ui->msgStreamTableView->verticalScrollBar()->setValue(0);
}

void MessageStreamWidget::on_scrollBottomBtn_clicked()
{
    //const bool success = msgStream->fetchNext();
    //qDebug() << __PRETTY_FUNCTION__ << " -- " << success;
    msgStream->fetchBottom();
    ui->msgStreamTableView->verticalScrollBar()->setValue(
                ui->msgStreamTableView->verticalScrollBar()->maximum()
                );
}

void MessageStreamWidget::on_followUpCheckBox_toggled(bool checked)
{
    msgStream->setContinuousFlag(checked);
}

void MessageStreamWidget::on_clearStreamBtn_clicked()
{
    msgStream->clear();
}
