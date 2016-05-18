#ifndef R_VIS_LIFETIMER_H
#define R_VIS_LIFETIMER_H

#include <QObject>

class R_Vis_LifeTimer : public QObject
{
    Q_OBJECT
public:
    explicit R_Vis_LifeTimer(QObject *parent = 0);

signals:

public slots:
};

#endif // R_VIS_LIFETIMER_H