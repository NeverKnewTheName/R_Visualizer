#include "systemoverview.h"
#include "ui_systemoverview.h"

#include "sysoverviewgraphicsview.h"

SystemOverview::SystemOverview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemOverview)
{
    ui->setupUi(this);
    this->initVisualizerGraphicsView();
    connect(ui->visualizerGraphicsView->getObjectStore(), &SysOvrvObjectStore::objectAddedToStore, this, &SystemOverview::addNewObject);
    connect(ui->visualizerGraphicsView->getObjectStore(), &SysOvrvObjectStore::objectRemovedFromStore, this, &SystemOverview::removeObject);
}

SystemOverview::~SystemOverview()
{
    delete ui;
    delete this->square;
}

void SystemOverview::initVisualizerGraphicsView()
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
    sysOvrvObj = new SysOvrvObject();
    sysOvrvObj->setShape(3);
    scene->addItem(sysOvrvObj);
}

void SystemOverview::applyRole(UserRoleMngr::UserRole roleToSwitchTo)
{

}

void SystemOverview::newMessage(Data_PacketPtr ptr)
{
        QDateTime timeStamp = ptr->timestamp();
        quint16 id = ptr->frame().ID_Standard;
        QByteArray canData = ptr->frame().data;

        quint8 code = canData.at(0);

        if(code == 0x10u)
        {
            if(!this->square->getMyColor().name().compare( QColor(Qt::green).name()))
                this->square->setMyColor(QColor(Qt::blue));
            else
                this->square->setMyColor(QColor(Qt::green));
            this->square->update();
        }
        //SystemOverview::repaint();
}

void SystemOverview::addNewObject(SysOvrvObject *obj)
{
    scene->addItem(obj);
}

void SystemOverview::removeObject(SysOvrvObject *obj)
{
    scene->removeItem(obj);
}
