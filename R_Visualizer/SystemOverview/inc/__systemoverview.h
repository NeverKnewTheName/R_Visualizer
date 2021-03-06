/**
 * @file systemoverview.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief The System Overview Module
 */
#ifndef SYSTEMOVERVIEW_H
#define SYSTEMOVERVIEW_H


#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

class MainWindow;
class MessageConfig;

#include "userrolemngr.h"
#include "Msg.h"
#include "sysovrvobjectstore.h"
#include "sysovrvobject.h"


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
    explicit SystemOverview(const MessageConfig *msgConfig, QWidget *parent = 0);
    ~SystemOverview();

protected:
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    friend class MainWindow;
    void initVisualizerGraphicsView();

    Ui::SystemOverview *ui;
    const MessageConfig *msgConfig;

    QGraphicsScene SystemOverviewScene;
    SysOvrvObjectStore sysOvrvObjStore;

    Qt::KeyboardModifiers kbrdModifiers;

private slots:
    void slt_applyRole(UserRoleMngr::UserRole roleToSwitchTo);
    void slt_newMessage(const TimestampedMsg &newMsg);

    void slt_addNewObject(const QPointF &pos);
    void slt_removeObject(SysOvrvObject* obj);
    void slt_updateObject(SysOvrvObject *obj);
    void slt_duplicateObject(SysOvrvObject *obj);
};

#endif // SYSTEMOVERVIEW_H
