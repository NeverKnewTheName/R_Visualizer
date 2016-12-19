#ifndef SYSTEMOVERVIEW_H
#define SYSTEMOVERVIEW_H

#include "userrolemngr.h"
#include "can_packet.h"
#include "msg.h"

#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "sysovrvobject.h"

class MainWindow;

namespace Ui {
class SystemOverview;
}

/**
 * @brief The SystemOverview class is a QWidget that can be used to display \ref SysOvrvObjects.
 *
 * The SystemOverview handles certain mouse and key events and holds its own scene.
 */
class SystemOverview : public QWidget
{
    Q_OBJECT

public:
    explicit SystemOverview(QWidget *parent = 0);
    ~SystemOverview();

protected:
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    void initVisualizerGraphicsView();

    Ui::SystemOverview *ui;
    friend class MainWindow;

    QGraphicsScene SystemOverviewScene;
    Qt::KeyboardModifiers kbrdModifiers;

private slots:
    void applyRole(UserRoleMngr::UserRole roleToSwitchTo);
    void newMessage(Data_PacketPtr ptr);
    void addNewObject(SysOvrvObject* obj, QPointF &pos);
    void removeObject(SysOvrvObject* obj);
};

#endif // SYSTEMOVERVIEW_H
