#include "systemoverview.h"
#include "ui_systemoverview.h"

SystemOverview::SystemOverview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemOverview)
{
    ui->setupUi(this);
    this->initVisualizerGraphicsView();
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
}

void SystemOverview::applyRole(UserRoleMngr::UserRole roleToSwitchTo)
{

}
