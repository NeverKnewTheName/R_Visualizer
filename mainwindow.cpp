#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "idadddialog.h"
#include "msgtypeadddialog.h"

#include "msgdelegate.h"
#include "msgiddelegate.h"

#include "ideditordelegate.h"
#include "msgtypeeditordelegate.h"

#include <QFile>
#include <QFileDialog>

#include <QDateTime>

#define __DEBUG__

#ifdef __DEBUG__
#include <QDebug>
#endif //__DEBUG__

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->currentFileName = "";

    this->initIDTableView();
    this->initMsgTypeTableView();
    this->initMsgsTableView();
    this->msgModel->setIDModel(this->idModel);
    this->msgModel->setMsgTypeModel(this->msgTypeModel);
    this->initVisualizerGraphicsView();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete square;
}


void MainWindow::on_actionNew_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__
    //TESTING ONLY
    static int cntr = 0;
    MsgDataT msgData = { 0x2, cntr, 0x0,cntr,0x0,cntr,0x0,cntr};
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr++),0xFF,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr++),0xF0,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr++),0xF0,msgData));
    msgData = { 0x3, cntr, 0x0,cntr,0x0,cntr,0x0,cntr};
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr++),0xFF,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr++),0xFF,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr++),0xF0,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr++),0xFF,msgData));
}

void MainWindow::on_actionOpen_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    currentFileName = openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    //ToDO
    // read file content
    msgModel->parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
    // parse file
    // populate ui
    // close file
    jsonOpenFile.close();
}

void MainWindow::on_actionSave_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    if(currentFileName.isEmpty())
    {
        QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
        qDebug() << saveLoc;
        currentFileName = saveLoc;
    }
    QFile jsonSaveFile(currentFileName);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    }
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    jsonSaveFile.write(this->msgModel->parseToJSON()); //ToDO check for error (-1)
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MainWindow::on_actionConnect_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

}

void MainWindow::on_actionStart_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

}

void MainWindow::on_actionStop_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

}

void MainWindow::initMsgsTableView()
{
    msgModel = new MsgModel(this);

    ui->msgTableView->setModel(msgModel);
    ui->msgTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->msgTableView->horizontalHeader()->setStretchLastSection(true);
    ui->msgTableView->verticalHeader()->hide();
    ui->msgTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->msgTableView->setItemDelegate(new MsgDelegate(ui->msgTableView));
    ui->msgTableView->setItemDelegateForColumn(2, new MsgDelegate(this->msgTypeModel, ui->msgTableView));
    ui->msgTableView->setItemDelegateForColumn(1, new msgIDDelegate(this->idModel, ui->msgTableView));
    // scroll to the bottom as soon as a new row is inserted by
    // connecting the signal, which is fired once a row is inserted, with the scrollToBottom slot
    connect(msgModel, &MsgModel::rowsInserted, ui->msgTableView, &QTableView::scrollToBottom);
}

void MainWindow::initIDTableView()
{
    idModel = new IDModel(this);
    ui->idTableView->setModel(idModel);
    ui->idTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->idTableView->verticalHeader()->hide();
    ui->idTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    ui->idTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idTableView->setItemDelegate(new IDEditorDelegate(ui->idTableView));

    //ToDO scrollToBottom might not be the best slot to address....
    connect(idModel, &IDModel::rowsInserted, ui->idTableView, &QTableView::scrollToBottom);
    connect(idModel, &IDModel::internalModelChanged, ui->msgTableView, &QTableView::reset);
    //DEBUG//
//    idModel->add(0xFF, new IDRep(0xFF00, QString("Master"), QColor(Qt::blue)));
//    idModel->add(0xF0, new IDRep(0xF000, QString("PC"), QColor(Qt::green)));
    //DEBUG//
}

void MainWindow::initMsgTypeTableView()
{
    msgTypeModel = new MsgTypeModel(this);
    ui->msgTypeTableView->setModel(msgTypeModel);
    ui->msgTypeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->msgTypeTableView->verticalHeader()->hide();
    ui->msgTypeTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    ui->msgTypeTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->msgTypeTableView->setItemDelegate(new MsgTypeEditorDelegate(ui->msgTypeTableView));

    //ToDO scrollToBottom might not be the best slot to address....
    connect(msgTypeModel, &MsgTypeModel::rowsInserted, ui->msgTypeTableView, &QTableView::scrollToBottom);
    connect(msgTypeModel, &MsgTypeModel::internalModelChanged, ui->msgTableView, &QTableView::reset);
    //DEBUG//
//    msgTypeModel->add(new MsgTypeRep(0x02, QString("Start"), QColor(Qt::green)));
//    msgTypeModel->add(new MsgTypeRep(0x03, QString("Stop"), QColor(Qt::red)));
    //DEBUG//
}

void MainWindow::initVisualizerGraphicsView()
{
    //create a new scene
    scene = new QGraphicsScene(this);
    //set the graphicsview to the newly created scene
    ui->visualizerGraphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(6);

    ellipse = scene->addEllipse(10,10,100,100,blackPen,redBrush);
    rect = scene->addRect(-100,-100,50,50,blackPen,blueBrush);

    rect->setFlag(QGraphicsItem::ItemIsMovable);

    square = new MySquare();
    scene->addItem(square);
}

void MainWindow::on_idStoreBtn_clicked()
{

    QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
    qDebug() << saveLoc;
    QFile jsonSaveFile(saveLoc);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    }
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    jsonSaveFile.write(this->idModel->parseToJSON()); //ToDO check for error (-1)
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MainWindow::on_idLoadBtn_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    //ToDO
    // read file content
    idModel->parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
    // parse file
    // populate ui
    // close file
    jsonOpenFile.close();
}

void MainWindow::on_msgTypeSoreBtn_clicked()
{
    QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
    qDebug() << saveLoc;
    QFile jsonSaveFile(saveLoc);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    }
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    jsonSaveFile.write(this->msgTypeModel->parseToJSON()); //ToDO check for error (-1)
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MainWindow::on_msgTypeLoadBtn_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    //ToDO
    // read file content
    msgTypeModel->parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
    // parse file
    // populate ui
    // close file
    jsonOpenFile.close();
}

void MainWindow::on_idAddBtn_clicked()
{
    IDAddDialog *idAddDialogg = new IDAddDialog(this);
    connect(idAddDialogg, &IDAddDialog::commit, this, &MainWindow::idAddFinished);
    idAddDialogg->exec();
}

void MainWindow::idAddFinished(const int id, const QString name, const QColor color)
{
    idModel->add(id, new IDRep( name, color));
}

void MainWindow::on_msgTypeAddBtn_clicked()
{
    MsgTypeAddDialog *msgTypeAddDialogg = new MsgTypeAddDialog(this);
    connect(msgTypeAddDialogg, &MsgTypeAddDialog::commit, this, &MainWindow::msgTypeAddFinished);
    msgTypeAddDialogg->exec();
}

void MainWindow::msgTypeAddFinished(const int code, const QString message, const QColor color)
{
    msgTypeModel->add(code, new MsgTypeRep(code, message, color));
}

