#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>

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

    this->initMsgsTableView();
    this->initIDTableView();
    this->initMsgTypeTableView();
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
    msgModel->addMsg(new Msg(cntr++,0x120,0xFF55));
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
    ui->msgTableView->resizeRowsToContents();
    ui->msgTableView->resizeColumnsToContents();
    ui->msgTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
    ui->idTableView->resizeRowsToContents();
    ui->idTableView->resizeColumnsToContents();

    //ToDO scrollToBottom might not be the best slot to address....
    connect(idModel, &IDModel::rowsInserted, ui->idTableView, &QTableView::scrollToBottom);

    //DEBUG//
//    idModel->add(new IDRep(0xFF, QString("Master"), QColor(Qt::blue)));
//    idModel->add(new IDRep(0xF0, QString("PC"), QColor(Qt::green)));
    //DEBUG//
}

void MainWindow::initMsgTypeTableView()
{
    msgTypeModel = new MsgTypeModel(this);
    ui->msgTypeTableView->setModel(msgTypeModel);
    ui->msgTypeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->msgTypeTableView->verticalHeader()->hide();
    ui->msgTypeTableView->resizeRowsToContents();
    ui->msgTypeTableView->resizeColumnsToContents();
    //ui->msgTypeTableView->setEditTriggers(QAbstractItemView::DoubleClicked);

    //ToDO scrollToBottom might not be the best slot to address....
    connect(msgTypeModel, &MsgTypeModel::rowsInserted, ui->msgTypeTableView, &QTableView::scrollToBottom);

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
