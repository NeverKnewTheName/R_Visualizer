#include "systemoverview.h"
#include "ui_systemoverview.h"


#include <QWheelEvent>
#include <QScrollBar>
#include <QtMath>

#include <QDebug>

#include "messageconfig.h"
#include "sysovrvobjectstore.h"
#include "sysoverviewgraphicsview.h"

#include "sysovrvobjectdialog.h"

SystemOverview::SystemOverview(const MessageConfig *msgConfig, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemOverview),
    msgConfig(msgConfig),
    SystemOverviewScene(this),
    sysOvrvObjStore(this),
    kbrdModifiers(Qt::ControlModifier)
{
    ui->setupUi(this);
    /* this->initVisualizerGraphicsView(); */
    ui->visualizerGraphicsView->setScene(&SystemOverviewScene);

    connect(ui->visualizerGraphicsView, &SysOverviewGraphicsView::sgnl_addObjRequest, this, &SystemOverview::slt_addNewObject);
    connect(ui->visualizerGraphicsView, &SysOverviewGraphicsView::sgnl_removeObjRequest, this, &SystemOverview::slt_removeObject);
    connect(ui->visualizerGraphicsView, &SysOverviewGraphicsView::sgnl_updateObjRequest, this, &SystemOverview::slt_updateObject);
    connect(ui->visualizerGraphicsView, &SysOverviewGraphicsView::sgnl_duplicateObjRequest, this, &SystemOverview::slt_duplicateObject);

}

SystemOverview::~SystemOverview()
{
    delete ui;
}

void SystemOverview::wheelEvent(QWheelEvent *event)
{
    qDebug() << "wheelEvent";
    if(QApplication::keyboardModifiers() & Qt::ControlModifier)
    {
        ui->visualizerGraphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
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

//        const QPointF p1mouse = ui->visualizerGraphicsView->mapFromScene(p0scene);
//        const QPointF move = p1mouse - event->pos(); // The move
//        QScrollBar *scroller;
//        scroller = ui->visualizerGraphicsView->horizontalScrollBar();
//        scroller->setValue(move.x() + scroller->value());
//        scroller = ui->visualizerGraphicsView->verticalScrollBar();
//        scroller->setValue(move.y() + scroller->value());
    }
    else
    {
        QScrollBar *scroller;
        if(QApplication::keyboardModifiers() & Qt::AltModifier)
        {
            //Vertical scrollbar
            scroller = ui->visualizerGraphicsView->verticalScrollBar();
            qDebug() << "scroll vertical";
        }
        else
        {
            //horizontal scrollbar
            scroller = ui->visualizerGraphicsView->horizontalScrollBar();
            qDebug() << "scroll horizontal";
        }
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
    //    scene->setSceneRect(QRectF(QPointF(0,0),
    //                               ui->visualizerGraphicsView->maximumViewportSize()));
    //set the graphicsview to the newly created scene
}

void SystemOverview::slt_applyRole(UserRoleMngr::UserRole roleToSwitchTo)
{
    switch(roleToSwitchTo)
    {
        case UserRoleMngr::AdminRole:
            ui->visualizerGraphicsView->enableEditing(true);
            break;
        case UserRoleMngr::NormalUserRole:
            ui->visualizerGraphicsView->enableEditing(false);
            break;
        default:
            ui->visualizerGraphicsView->enableEditing(false);
            break;
    }
}

void SystemOverview::slt_newMessage(const Msg &newMsg)
{
    qDebug() << "SystemOverview received msg from ID:  " << newMsg.getId() << " with code: " << newMsg.getCode();
    /* ui->visualizerGraphicsView->getObjectStore()->receiveMessage(ptr); */
//    QDateTime timeStamp = ptr->timestamp();
//    const MsgIDType id = ptr->frame().ID_Standard;
//    QByteArray canData = ptr->frame().data;

//    quint8 code = canData.at(0);

//    if(code == 0x10u)
//    {
//        //            if(!this->square->getMyColor().name().compare( QColor(Qt::green).name()))
//        //                this->square->setMyColor(QColor(Qt::blue));
//        //            else
//        //                this->square->setMyColor(QColor(Qt::green));
//        //            this->square->update();
//    }
//    //SystemOverview::repaint();
//    
}

void SystemOverview::slt_addNewObject(const QPointF &pos)
{
    SysOvrvObjectDialog addSysOvrvObjectDialog(this);
    connect(&addSysOvrvObjectDialog, &SysOvrvObjectDialog::sgnl_commit, [=](SysOvrvObject *obj){
            SystemOverviewScene.addItem(obj);
            qDebug() << "Item: " << obj->getObjName() << " added to scene at pos: " << pos;
            obj->setPos(pos);
            });
    addSysOvrvObjectDialog.exec();
}

void SystemOverview::slt_removeObject(SysOvrvObject *obj)
{
    if(obj == nullptr)
    {
        return;
    }
    SystemOverviewScene.removeItem(obj);
    sysOvrvObjStore.removeObject(obj);
    delete obj;
}

void SystemOverview::slt_updateObject(SysOvrvObject *obj)
{
    if(obj == nullptr)
    {
        return;
    }
    SysOvrvObjectDialog updateSysOvrvObjectDialog(obj, this);

    const QPointF &retrievedPos = obj->pos();

    connect(&updateSysOvrvObjectDialog, &SysOvrvObjectDialog::sgnl_commit, [=](SysOvrvObject *obj){
    sysOvrvObjStore.updateObject(obj);
            SystemOverviewScene.addItem(obj);
            obj->setPos(retrievedPos);
            sysOvrvObjStore.updateObject(obj);
            });
    updateSysOvrvObjectDialog.exec();
}

void SystemOverview::slt_duplicateObject(SysOvrvObject *obj)
{
    if(obj == nullptr)
    {
        return;
    }
    SysOvrvObject *duplicatedObj = obj->clone();
    duplicatedObj->setParentItem(Q_NULLPTR);
    SystemOverviewScene.addItem(duplicatedObj);
    duplicatedObj->moveBy(10,10);
    sysOvrvObjStore.addObject(duplicatedObj);
}
