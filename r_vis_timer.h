#ifndef R_VIS_TIMER_H
#define R_VIS_TIMER_H

#include <QObject>
#include <QTimer>
#include <stdint.h>

#define MAX_TMR_RES 0xFFFFu

typedef uint16_t TimerResolution;

typedef unsigned int TimerInterval;

typedef enum cntDirEnum
{
    CntUP,
    CntDOWN
}CntDir;

class R_Vis_Timer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool ovfFlag READ ovfFlag WRITE setOvfFlag NOTIFY timerIRQ_OVF)
    Q_PROPERTY(bool cmpFlag READ cmpFlag WRITE setCmpFlag NOTIFY timerIRQ_CMPMatch)


public:
    explicit R_Vis_Timer(TimerInterval intervalInMs, QObject *parent = 0);

    TimerResolution curVal() const;
    void setCurVal(const TimerResolution &curVal);

    TimerResolution cmpVal() const;
    void setCmpVal(const TimerResolution &cmpVal);

    TimerResolution startVal() const;
    void setStartVal(const TimerResolution &startVal);

    CntDir counterDirection() const;
    void setCounterDirection(CntDir counterDirection);

    bool reloadOnOVFEnable() const;
    void setReloadOnOVFEnable(bool reloadOnOVFEnable);

    bool intOVFEnable() const;
    void setIntOVFEnable(bool intOVFEnable);

    bool intCMPEnable() const;
    void setIntCMPEnable(bool intCMPEnable);

    bool ovfFlag() const;
    void setOvfFlag(bool ovfFlag);

    bool cmpFlag() const;
    void setCmpFlag(bool cmpFlag);

signals:
    void timerIRQ_OVF(); // Timer has overflowed
    void timerIRQ_CMPMatch(); // Timer value equals compare match

public slots:
    void startTimer(); // start the timer from the specified start value
    void stopTimer();  // stop the timer, do not update start value
    void resetTimer(); // set current value back to start value, do not stop timer

private slots:
    void incTimer(); // Increment the timer

private:
    // Timer values
    TimerResolution m_curVal;  // current value of the timer
    TimerResolution m_cmpVal;  // compare match value
    TimerResolution m_startVal; // start value of the timer

    // Timer configuration
    CntDir m_counterDirection;  // UP/DOWN Counter
    bool m_reloadOnOVFEnable; // Reload the timer with the startVal in case of overflow or stop the timer
    bool m_intOVFEnable; // generate interrupt in case of overflow
    bool m_intCMPEnable; // generate interrupt in case of compare match

    // Timer flags
    bool m_ovfFlag;  // status flag: timer overflowed
    bool m_cmpFlag;  // status flag: compare match

    // 'HW' Timer
    QTimer *m_timer;
};

#endif // R_VIS_TIMER_H
