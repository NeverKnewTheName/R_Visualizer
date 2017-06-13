/**
 * @file SysOverviewTextLabel.h
 * @author Christian Neuberger
 * @date 2017-05-02
 * 
 * @brief System Overview Text Label
 */
#ifndef SYSOVERVIEWTEXTLABEL_H
#define SYSOVERVIEWTEXTLABEL_H

#include <QGraphicsSimpleTextItem>

#include "ISysOverviewLabelTrigger.h"

/**
 * @brief The SysOverviewTextLabel
 */
class SysOverviewTextLabel : public QGraphicsSimpleTextItem
{
public:
    SysOverviewTextLabel(
            const QString &text = QString(""),
            QGraphicsItem *parent = Q_NULLPTR
            );

    SysOverviewTextLabel(
            const SysOverviewTextLabel &copy
            );

    virtual ~SysOverviewTextLabel();

    void setEditable(const bool enable);
    bool isEditable() const;

    void textEdit(QWidget *widget);
    void setLabelText(const QString &text);

    void trigger(const IMsg &msg);

    void addTrigger(SysOvrvLabelTriggerPtr trigger);
    QVector<SysOvrvLabelTriggerPtr> getTriggers();

    // QGraphicsItem interface
protected:
    void contextMenuEvent(
            QGraphicsSceneContextMenuEvent *event
            ) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

private:
    bool editable;
    bool doubleClicked;
    QVector<SysOvrvLabelTriggerPtr> labelTrigger;

};

#endif /* SYSOVERVIEWTEXTLABEL_H */
