#include "r_vis_timer.h"

R_Vis_Timer::R_Vis_Timer(TimerInterval intervalInMs, QObject *parent) : QObject(parent)
{
    this->m_ovfFlag = false;
    this->m_cmpFlag = false;

    this->m_startVal = 0;
    this->m_curVal = 0;
    this->m_cmpVal = 0;

    this->m_counterDirection = CntUP;
    this->m_intCMPEnable = false;
    this->m_intOVFEnable = false;
    this->m_reloadOnOVFEnable = false;

    this->m_timer = new QTimer(this);
    this->m_timer->setInterval(intervalInMs);

    // everytime the QTimer timeouts this timer's curVal is incremented
    connect(this->m_timer, &QTimer::timeout,
            this, &R_Vis_Timer::incTimer);
}

void R_Vis_Timer::startTimer()
{
    this->m_curVal = this->m_startVal;
    this->m_timer->start();
}

void R_Vis_Timer::stopTimer()
{
    this->m_timer->stop();
}

void R_Vis_Timer::resetTimer()
{
    this->m_curVal = 0;
}

void R_Vis_Timer::incTimer()
{
    ++(this->m_curVal); // increment timer value
    // if the interrupt generation for compare match is enabled and the compare match is hit, fire interrupt
    if((this->m_curVal == this->m_cmpVal) && (this->m_intCMPEnable))
    {
        this->m_cmpFlag = true;
        emit timerIRQ_CMPMatch();
    }
    // if the interrupt generation for timer overflow is enabled and the timer overflows, fire interrupt
    if((this->m_curVal == MAX_TMR_RES) && (this->m_intOVFEnable))
    {
        this->m_ovfFlag = true;
        emit timerIRQ_OVF();

        if(this->m_reloadOnOVFEnable)
        {
            this->m_curVal = this->m_startVal;
        }
        else
        {
            this->m_timer->stop();
        }
    }
}

bool R_Vis_Timer::cmpFlag() const
{
    return m_cmpFlag;
}

void R_Vis_Timer::setCmpFlag(bool cmpFlag)
{
    m_cmpFlag = cmpFlag;
}

bool R_Vis_Timer::ovfFlag() const
{
    return m_ovfFlag;
}

void R_Vis_Timer::setOvfFlag(bool ovfFlag)
{
    m_ovfFlag = ovfFlag;
}

bool R_Vis_Timer::intCMPEnable() const
{
    return m_intCMPEnable;
}

void R_Vis_Timer::setIntCMPEnable(bool intCMPEnable)
{
    m_intCMPEnable = intCMPEnable;
}

bool R_Vis_Timer::intOVFEnable() const
{
    return m_intOVFEnable;
}

void R_Vis_Timer::setIntOVFEnable(bool intOVFEnable)
{
    m_intOVFEnable = intOVFEnable;
}

bool R_Vis_Timer::reloadOnOVFEnable() const
{
    return m_reloadOnOVFEnable;
}

void R_Vis_Timer::setReloadOnOVFEnable(bool reloadOnOVFEnable)
{
    m_reloadOnOVFEnable = reloadOnOVFEnable;
}

CntDir R_Vis_Timer::counterDirection() const
{
    return m_counterDirection;
}

void R_Vis_Timer::setCounterDirection(CntDir counterDirection)
{
    m_counterDirection = counterDirection;
}

TimerResolution R_Vis_Timer::startVal() const
{
    return m_startVal;
}

void R_Vis_Timer::setStartVal(const TimerResolution &startVal)
{
    m_startVal = startVal;
}

TimerResolution R_Vis_Timer::cmpVal() const
{
    return m_cmpVal;
}

void R_Vis_Timer::setCmpVal(const TimerResolution &cmpVal)
{
    m_cmpVal = cmpVal;
}

TimerResolution R_Vis_Timer::curVal() const
{
    return m_curVal;
}

void R_Vis_Timer::setCurVal(const TimerResolution &curVal)
{
    m_curVal = curVal;
}

