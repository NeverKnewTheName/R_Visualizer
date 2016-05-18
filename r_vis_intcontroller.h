#ifndef R_VIS_INTCONTROLLER_H
#define R_VIS_INTCONTROLLER_H

#include <QObject>

class R_Vis_IntController : public QObject
{
    Q_OBJECT
public:
    explicit R_Vis_IntController(QObject *parent = 0);

signals:

public slots:
};

#endif // R_VIS_INTCONTROLLER_H