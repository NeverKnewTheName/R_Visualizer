#ifndef SYSOVRVOBJECT_H
#define SYSOVRVOBJECT_H

#include <QGraphicsItem>
#include <QHash>
#include <QImage>
#include <QPixmap>

#include "resizerectcorner.h"
#include "sysovrvtextlabel.h"
#include "sysovrvtrigger.h"
#include "msg.h"

class SysOvrvObject : public QGraphicsItem
{
public:
    typedef enum _ObjShapeType
    {
        ObjShape_Rectangle,
        ObjShape_Square,
        ObjShape_Ellipse,
        ObjShape_Circle,
        ObjShape_Triangle,
        ObjShape_Image
    }ObjShapeType;

    explicit SysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    ~SysOvrvObject();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void setupSysOvrvObject();

    QColor getMyColor() const;
    void setMyColor(const QColor &value);

    QString getObjName() const;
    void setObjName(const QString &value);

    void loadImageFromFile();
    void loadImageFromFile(QString &FilePath);

    void setShape(ObjShapeType shape);
    ObjShapeType getShape() const;

    SysOvrvTextLabel * addLabel();
    SysOvrvTextLabel * addLabel(SysOvrvTextLabel *label);
    SysOvrvTextLabel * addLabel(QString text, qreal x, qreal y);

    SysOvrvObject *duplicate(SysOvrvObject *parentObj = NULL);

    void setAsChild(bool isChild);
    bool isAChild() const;

    void setResizeMode(bool modeON, bool propagateToChildObjs = true);
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

    void addTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *newTrigger);
    void addChildsTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *newChildTrigger);
    void removeTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *triggerToRemove);
    void removeChildsTrigger(const MsgIDType id, const MsgCodeType code, SysOvrvTrigger *triggerToRemove);
    void msgReceived(const MsgIDType id, const MsgCodeType code, QByteArray &canData);
    QList<MsgIDType> getTriggerIDs() const;
    QList<MsgCodeType> getTriggerCodesToID(const MsgIDType id) const;
    QVector<SysOvrvTrigger *> getTriggersToIDandCode(const MsgIDType id, const MsgCodeType code);

    QPixmap getObjPixMap() const;
    void setObjPixMap(const QPixmap &value);

    void update(const QRectF &rect = QRectF());

private:
    QRectF m_BoundingRect;
    ResizeRectCorner *corners;
    static unsigned int objCntr;
    const unsigned int localObjCntr;
    bool isInResizeMode;
    bool isChildObject;
    bool doubleClicked;
    QString objName;
    QColor myColor;
    ObjShapeType shapeType;
    QPixmap ObjPixMap;

    QVector<SysOvrvObject *> childSysOvrvObjects;
    QVector<SysOvrvTextLabel*> objTextlabels;
    QHash<MsgIDType, QHash<MsgCodeType, QVector<SysOvrvTrigger*>>> GlobalTriggerStore;
    QHash<MsgIDType, QHash<MsgCodeType, QVector<SysOvrvTrigger*>>> LocalTriggerStore;

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
