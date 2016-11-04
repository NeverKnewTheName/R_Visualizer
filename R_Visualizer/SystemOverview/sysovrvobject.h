#ifndef SYSOVRVOBJECT_H
#define SYSOVRVOBJECT_H

#include <QGraphicsItem>
#include <QHash>

#include "resizerectcorner.h"
#include "sysovrvtextlabel.h"
#include "sysovrvtrigger.h"

class SysOvrvObject : public QGraphicsItem
{
public:
    explicit SysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
//    explicit SysOvrvObject(SysOvrvObject *obj, QGraphicsItem *parent = Q_NULLPTR);
    ~SysOvrvObject();

    typedef enum Shapetypes
    {
        ObjShape_Rectangle,
        ObjShape_Square,
        ObjShape_Ellipse,
        ObjShape_Circle,
        ObjShape_Triangle
    }ObjShapeTypes;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void setupSysOvrvObject();

    QColor getMyColor() const;
    void setMyColor(const QColor &value);

    QString getObjName() const;
    void setObjName(const QString &value);

    void setShape(ObjShapeTypes shape);
    ObjShapeTypes getShape() const;

    SysOvrvTextLabel * addLabel();
    SysOvrvTextLabel * addLabel(SysOvrvTextLabel *label);
    SysOvrvTextLabel * addLabel(QString text, qreal x, qreal y);

    SysOvrvObject *duplicate(SysOvrvObject *parentObj = NULL);

    void setAsChild(bool isChild);
    bool isAChild() const;

    void setResizeMode(bool modeON);
    bool getIsInResizeMode() const;
    void showResizeCorners(bool show);

    qreal getWidth() const;
    void setWidth(qreal newWidth);
    void adjustWidth(qreal factor);
    qreal getHeight() const;
    void setHeight(qreal newHeight);
    void adjustHeight(qreal factor);

    SysOvrvObject *addChildSysOvrvItem(SysOvrvObject* child);
    void removeChildSysOvrvItem(SysOvrvObject *child);
    QVector<SysOvrvObject *> &getChidSysOvrvObjects();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QString getHashedName() const;

    QByteArray parseToJson() const;
    void parseFromJson(QByteArray &jsonByteArray);

    void addTrigger(quint16 id, quint8 code, SysOvrvTrigger *newTrigger);
    void addChildsTrigger(quint16 id, quint8 code, SysOvrvTrigger *newChildTrigger);
    void removeTrigger(quint16 id, quint8 code, SysOvrvTrigger *triggerToRemove);
    void removeChildsTrigger(quint16 id, quint8 code, SysOvrvTrigger *triggerToRemove);
    void msgReceived(quint16 id, quint8 code, QByteArray &canData);
    QList<quint16> getTriggerIDs() const;
    QList<quint8> getTriggerCodesToID(quint16 id) const;
    QVector<SysOvrvTrigger*> getTriggersToIDandCode(quint16 id, quint8 code) const;

private:
    static int objCntr;
    int localObjCntr;
    bool isInResizeMode;
    bool isChildObject;
    bool doubleClicked;
    QString objName;
    QVector<SysOvrvTextLabel*> objTextlabels;
    QHash<quint16, QHash<quint8, QVector<SysOvrvTrigger*>>> GlobalTriggerStore;
    QHash<quint16, QHash<quint8, QVector<SysOvrvTrigger*>>> LocalTriggerStore;
    QColor myColor;
    ObjShapeTypes shapeType;
    QVector<SysOvrvObject *> childSysOvrvObjects;
    ResizeRectCorner *corners;
    QRectF m_BoundingRect;

    void updateCorners();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

};

#endif // SYSOVRVOBJECT_H
