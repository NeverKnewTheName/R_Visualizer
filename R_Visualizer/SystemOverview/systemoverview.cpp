#include "systemoverview.h"
#include "ui_systemoverview.h"

#include "sysoverviewgraphicsview.h"

#include <QWheelEvent>
#include <QScrollBar>
#include <QtMath>

SystemOverview::SystemOverview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemOverview),
    kbrdModifiers(Qt::ControlModifier)
{
    ui->setupUi(this);
    this->initVisualizerGraphicsView();
    connect(ui->visualizerGraphicsView->getObjectStore(), &SysOvrvObjectStore::objectAddedToStore, this, &SystemOverview::addNewObject);
    connect(ui->visualizerGraphicsView->getObjectStore(), &SysOvrvObjectStore::objectRemovedFromStore, this, &SystemOverview::removeObject);
}

SystemOverview::~SystemOverview()
{
    delete ui;
}

void SystemOverview::wheelEvent(QWheelEvent *event)
{
    if(QApplication::keyboardModifiers() == kbrdModifiers)
    {
//        ui->visualizerGraphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        //        const int degrees = event->delta();

        //        double scaleFactor = 1.15; //How fast we zoom

        //        if(steps > 0)
        //        {
        //            ui->visualizerGraphicsView->scale(scaleFactor,scaleFactor);
        //        }
        //        else
        //        {
        //            ui->visualizerGraphicsView->scale(1.0/scaleFactor,1.0/scaleFactor);
        //        }
        const QPointF p0scene = ui->visualizerGraphicsView->mapToScene(event->pos());

        qreal factor = qPow(1.2, event->delta() / 240.0);
        ui->visualizerGraphicsView->scale(factor, factor);

        const QPointF p1mouse = ui->visualizerGraphicsView->mapFromScene(p0scene);
        const QPointF move = p1mouse - event->pos(); // The move
        QScrollBar *scroller;
        scroller = ui->visualizerGraphicsView->horizontalScrollBar();
        scroller->blockSignals(true);
        scroller->setValue(move.x() + scroller->value());
        scroller = ui->visualizerGraphicsView->verticalScrollBar();
        scroller->blockSignals(true);
        scroller->setValue(move.y() + scroller->value());
    }
    else
    {
        QScrollBar *scroller;
        scroller = ui->visualizerGraphicsView->horizontalScrollBar();
        scroller->blockSignals(false);
        scroller = ui->visualizerGraphicsView->verticalScrollBar();
        scroller->blockSignals(false);

        QWidget::wheelEvent(event);
    }
}

void SystemOverview::keyPressEvent(QKeyEvent *event)
{

}

void SystemOverview::keyReleaseEvent(QKeyEvent *event)
{

}

void SystemOverview::initVisualizerGraphicsView()
{
    //create a new scene
    scene = new QGraphicsScene(this);

    //    scene->setSceneRect(QRectF(QPointF(0,0),
    //                               ui->visualizerGraphicsView->maximumViewportSize()));
    //set the graphicsview to the newly created scene
    ui->visualizerGraphicsView->setScene(scene);
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
        //            if(!this->square->getMyColor().name().compare( QColor(Qt::green).name()))
        //                this->square->setMyColor(QColor(Qt::blue));
        //            else
        //                this->square->setMyColor(QColor(Qt::green));
        //            this->square->update();
    }
    //SystemOverview::repaint();
}

void SystemOverview::addNewObject(SysOvrvObject *obj, QPointF &pos)
{
    scene->addItem(obj);
    qDebug() << "Item: " << obj->getObjName() << " added to scene at pos: " << pos;
    obj->setPos(pos);
}

void SystemOverview::removeObject(SysOvrvObject *obj)
{
    scene->removeItem(obj);
}
