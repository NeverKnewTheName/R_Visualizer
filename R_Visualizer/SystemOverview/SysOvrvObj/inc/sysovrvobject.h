#ifndef SYSOVRVOBJECT_H
#define SYSOVRVOBJECT_H

#include <QGraphicsItem>
#include <QHash>
#include <QImage>
#include <QPixmap>

#include "resizeablegraphicsitem.h"
#include "sysovrvtextlabel.h"
#include "sysovrvtrigger.h"
#include "msg.h"

/**
 * @brief The SysOvrvObject class is a graphical object that represents a part of the system or is a part of another object.
 */
class SysOvrvObject : public ResizableGraphicsItem
{
public:
    enum { Type = UserType + 2 };
    typedef enum _ObjShapeType
    {
        ObjShape_Rectangle,
        ObjShape_Square,
        ObjShape_Ellipse,
        ObjShape_Circle,
        ObjShape_Triangle,
        ObjShape_Image,
        NR_of_ObjShapes
    }ObjShapeType;
    /* Q_ENUM(_ObjShapeType) */

    SysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    SysOvrvObject(const SysOvrvObject &ToCopy);
    SysOvrvObject(SysOvrvObject &&ToMove);
    virtual ~SysOvrvObject();

    virtual SysOvrvObject *clone() const = 0;
    virtual SysOvrvObject *move() = 0;

    static QString translateObjShapeTypeToString(ObjShapeType type);
    static QStringList getShapesAsStringList();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
    int type() const;


    QColor getObjColor() const;
    QColor getCurObjColor() const;
    void setObjColor(const QColor &value);

    QString getObjName() const;
    void setObjName(const QString &value);

    virtual ObjShapeType getShape() const = 0;

    void selectObject(const bool isSelected = true);

    /**
     * @brief addLabel adds a new \ref SysOvrvTextLabel to the \ref SysOvrvObject by creating a new \ref SysOvrvTextLabel
     * @return Returns the newly created \ref SysOvrvTextLabel
     */
    SysOvrvTextLabel * addLabel();
    /**
     * @brief addLabel adds the given \ref SysOvrvTextLabel to the \ref SysOvrvObject
     * @param label \ref SysOvrvTextLabel to add to the \ref SysOvrvObject
     * @return Returns the added \ref SysOvrvTextLabel
     */
    SysOvrvTextLabel * addLabel(SysOvrvTextLabel *label);
    /**
     * @brief addLabel adds a new \ref SysOvrvTextLabel to the \ref SysOvrvObject with the given paramters
     * @param text
     * @param x
     * @param y
     * @return
     */
    SysOvrvTextLabel * addLabel(const QString &text, const qreal x, const qreal y);
    //DEPRECATED
    void removeLabel(SysOvrvTextLabel *label);

    /**
     * @brief duplicate duplicates the current \ref SysOvrvObject and returns the dubplicated object
     * @param parentObj Optional Parent Object for the duplicated object
     * @return Returns the duplicated \ref SysOvrvObject
     *
     * \note If no parentObj is provided, the hierarchy of the current \ref SysOvrvObject is kept
     * \note If a parentObj is provided, it will take the role of the parent for the duplicated \ref SysOvrvObject
     */
    SysOvrvObject *duplicate(SysOvrvObject *parentObj = Q_NULLPTR);

    void setAsChild(bool isChild);
    bool isAChild() const;

    QVector<SysOvrvObject *> getChildSysOvrvObjects();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QString getHashedName() const;

    QByteArray parseToJson() const;
    void parseFromJson(QByteArray &jsonByteArray);

    void setParentSysOvrvObj(SysOvrvObject *parentSysOvrvObj);

    void enableEdit(bool enable = true);
    void enableChildrenEdit(bool enable = true);

private:
    static unsigned int objCntr;
    const unsigned int localObjCntr;
    QRectF m_BoundingRect;
    QString objName;
    QColor objColor;
    bool isChildObject;
    bool isEditable;
    bool doubleClicked;

    void setupSysOvrvObject();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

    // ResizableGraphicsItem interface
public:
    virtual void resize(const ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y) Q_DECL_OVERRIDE;
    virtual void setWidth(const qreal newWidth) Q_DECL_OVERRIDE;
    virtual qreal getWidth() const Q_DECL_OVERRIDE;
    virtual void setHeight(const qreal newHeight) Q_DECL_OVERRIDE;
    virtual qreal getHeight() const Q_DECL_OVERRIDE;
};

#endif // SYSOVRVOBJECT_H
