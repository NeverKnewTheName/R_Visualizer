#ifndef ISYSOVERVIEWOBJECTMANAGERSUBWIDGET_H
#define ISYSOVERVIEWOBJECTMANAGERSUBWIDGET_H

#include <QWidget>

#include "ISystemOverviewObject.h"

class ISysOverviewObjectManagerSubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ISysOverviewObjectManagerSubWidget(QWidget *parent = 0);
    virtual ~ISysOverviewObjectManagerSubWidget();

    virtual void updateSysOverviewObject(ISysOvrvObjPtr sysOvrvObj) = 0;
//    virtual void setupWidet();
signals:

public slots:
};

#endif // ISYSOVERVIEWOBJECTMANAGERSUBWIDGET_H
