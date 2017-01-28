#ifndef SYSOVRVTEXTLABEL_H
#define SYSOVRVTEXTLABEL_H

#include <QGraphicsSimpleTextItem>

class SysOvrvTextLabel : public QGraphicsSimpleTextItem
{
public:
    enum { Type = UserType + 5 };
    SysOvrvTextLabel(QGraphicsItem *parent = Q_NULLPTR);
    SysOvrvTextLabel(const QString &text, QGraphicsItem *parent = Q_NULLPTR);
    SysOvrvTextLabel(const SysOvrvTextLabel &ToCopy);

    void setEditable(bool enable);
    void textEdit();

    QByteArray parseToJson() const;
    void parseFromJson(QByteArray &jsonByteArray);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_bDoubleClicked;
    bool m_bEditable;

    // QGraphicsItem interface
public:
    int type() const;

    // QGraphicsItem interface
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SYSOVRVTEXTLABEL_H
