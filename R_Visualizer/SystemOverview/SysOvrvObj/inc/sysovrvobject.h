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

    SysOvrvObject(QGraphicsItem *parent = Q_NULLPTR);
    SysOvrvObject(const SysOvrvObject &ToCopy);
    SysOvrvObject(SysOvrvObject &&ToMove);
    virtual ~SysOvrvObject();

    static QString translateObjShapeTypeToString(ObjShapeType type);
    static QStringList getShapesAsStringList();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    int type() const;


    QColor getMyColor() const;
    void setMyColor(const QColor &value);

    QString getObjName() const;
    void setObjName(const QString &value);

    /**
     * @brief loadImageFromFile loads an image file into the \ref SysOvrvObject that is selected via an file open dialog
     * @param parent The QWidget the file open dialog shall be spawned in
     */
    void loadImageFromFile(QWidget *parent = Q_NULLPTR);
    /**
     * @brief loadImageFromFile loads an image file into the \ref SysOvrvObject specified by the FilePath
     * @param FilePath Path to the image file to load
     */
    void loadImageFromFile(const QString &FilePath);

    /**
     * @brief setShape sets the shape of the \ref SysOvrvObject to the specified shape
     * @param shape Shape to set the \ref SysOvrvObject to
     *
     * \note This function will call \ref updateShape to force a redrawing of the internal QPixMap
     *
     */
    void setShape(ObjShapeType shape);
    /**
     * @brief getShape Returns the current shape of the \ref SysOvrvObject as a \ref ObjShapeType
     * @return Current shape as a \ref ObjShapeType
     */
    ObjShapeType getShape() const;

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
    SysOvrvTextLabel * addLabel(const QString &text, qreal x, qreal y);
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

    QVector<SysOvrvObject *> getChidSysOvrvObjects();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QString getHashedName() const;

    QByteArray parseToJson() const;
    void parseFromJson(QByteArray &jsonByteArray);

    QPixmap getObjPixMap() const;
    void setObjPixMap(const QPixmap &value);


    void setParentSysOvrvObj(SysOvrvObject *parentSysOvrvObj);

    void enableEdit(bool enable = true);
    void enableChildrenEdit(bool enable = true);

private:
    static unsigned int objCntr;
    const unsigned int localObjCntr;
    QRectF m_BoundingRect;
    QString objName;
    QColor myColor;
    ObjShapeType shapeType;
    bool isChildObject;
    bool isEditable;
    bool doubleClicked;
    QPixmap ObjPixMap;

    void updateShape(const QRectF &rect = QRectF());
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
    void resize(ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y);
    void setWidth(const qreal newWidth);
    qreal getWidth() const;
    void setHeight(const qreal newHeight);
    qreal getHeight() const;
};



#endif // SYSOVRVOBJECT_H
