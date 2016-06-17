#ifndef SYSTEMOVERVIEW_H
#define SYSTEMOVERVIEW_H

#include "userrolemngr.h"
#include "can_packet.h"
#include "msg.h"

#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "mysquare.h"

class MainWindow;

namespace Ui {
class SystemOverview;
}

class SystemOverview : public QWidget
{
    Q_OBJECT

public:
    explicit SystemOverview(QWidget *parent = 0);
    ~SystemOverview();

private:
    void initVisualizerGraphicsView();

    Ui::SystemOverview *ui;
    friend class MainWindow;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    MySquare *square;

private slots:
    void applyRole(UserRoleMngr::UserRole roleToSwitchTo);
    void newMessage(CAN_PacketPtr ptr);
};

#endif // SYSTEMOVERVIEW_H
