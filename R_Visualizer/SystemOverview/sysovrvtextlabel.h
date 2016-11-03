#ifndef SYSOVRVTEXTLABEL_H
#define SYSOVRVTEXTLABEL_H

#include <QGraphicsSimpleTextItem>

class SysOvrvTextLabel : public QGraphicsSimpleTextItem
{
public:
    SysOvrvTextLabel(QGraphicsItem *parent = Q_NULLPTR);

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
};

#endif // SYSOVRVTEXTLABEL_H
