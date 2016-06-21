#include "msgtableview.h"

#include <QDateTime>
#include <QDebug>

MsgTableView::MsgTableView(QWidget *parent) :
    QTableView(parent),
    visibleRows(VISIBLE_ROWS),
    visibleRowCntr(0),
    visibleRowOffset(0),
    visibleRowOffsetHIGH(0),
    continuousScrolling(true),
    bottomEnd(false),
    topEnd(true),
    idFilterEnabled(false),
    codeFilterEnabled(false),
    timestampFromFilterEnabled(false),
    timestampToFilterEnabled(false)
{

}

unsigned int MsgTableView::getVisibleRows() const
{
    return visibleRows;
}

void MsgTableView::setVisibleRows(unsigned int value)
{
    visibleRows = value;
}

FilterIDStore *MsgTableView::getFilterIDModel() const
{
    return filterIDModel;
}

void MsgTableView::setFilterIDModel(FilterIDStore *value)
{
    filterIDModel = value;
}

FilterCodeStore *MsgTableView::getFilterCodeModel() const
{
    return filterCodeModel;
}

void MsgTableView::setFilterCodeModel(FilterCodeStore *value)
{
    filterCodeModel = value;
}

FilterTimestampStore *MsgTableView::getFilterTimestampModel() const
{
    return filterTimestampModel;
}

void MsgTableView::setFilterTimestampModel(FilterTimestampStore *value)
{
    filterTimestampModel = value;
}

bool MsgTableView::isAtBottomEnd()
{
    return bottomEnd || (visibleRowOffset == 0);
}

bool MsgTableView::isAtTopEnd()
{
    return topEnd || (!isRowHidden(model()->rowCount()-1));
}

bool MsgTableView::isLegit(unsigned int rowNr) const
{
    bool isLegit = true;

    if(idFilterEnabled)
    {
        isLegit = isLegit && filterIDModel->containsID(this->model()->index(rowNr, 1).data(Qt::UserRole+3).value<unsigned int>());
    }
    if(isLegit && codeFilterEnabled)// abort instantly if already not legit
    {
        isLegit = isLegit && filterCodeModel->containsCode(this->model()->index(rowNr, 2).data(Qt::UserRole+3).value<unsigned int>());
    }
    if(isLegit && ((timestampFromFilterEnabled)||(timestampToFilterEnabled)))// abort instantly if already not legit
    {
        QDateTime timestamp = this->model()->index(rowNr, 0).data(Qt::UserRole+3).value<QDateTime>();

        if(timestampFromFilterEnabled)
        {
            isLegit = isLegit && filterTimestampModel->isValidTimestampFrom(timestamp);
        }
        if(isLegit && timestampToFilterEnabled) // abort instantly if already not legit
        {
            isLegit = isLegit && filterTimestampModel->isValidTimestampTo(timestamp);
        }
    }
    return isLegit;
}

void MsgTableView::reset()
{
    visibleRowCntr = 0;
    visibleRowOffset = 0;
    visibleRowOffsetHIGH = 0;
    continuousScrolling = true;
    QTableView::reset();
}

void MsgTableView::rowAdded(unsigned int rowNr)
{
    // rows have been added!
    if(!continuousScrolling || !isLegit(rowNr))
    {
        setRowHidden(rowNr, true);
        if(isLegit(rowNr))
        {
            qDebug() << "No continuous scrolling";
            topEnd = false;
        }
    }
    else
    {
        visibleRowCntr++;
        visibleRowOffsetHIGH = rowNr;
        if( visibleRowCntr > visibleRows)
        {
            emit invisibleRows(true);
            while(isRowHidden(visibleRowOffset))
                visibleRowOffset++;
            setRowHidden(visibleRowOffset, true);
            visibleRowOffset++;
            visibleRowCntr--;
        }else
        {
            emit invisibleRows(false);
        }
        this->resizeRowToContents(rowNr);
        scrollTo(model()->index(rowNr, 3),QAbstractItemView::PositionAtBottom);
    }
}

void MsgTableView::filterChanged()
{
    unsigned int curRow = model()->rowCount();

    visibleRowCntr = 0;
    visibleRowOffsetHIGH = 0;
    while(curRow)
    {
        curRow--;
        if(isLegit(curRow))
        {
            visibleRowCntr++;
            if(!visibleRowOffsetHIGH)
                visibleRowOffsetHIGH = curRow;
            if(isRowHidden(curRow))
            {
                setRowHidden(curRow, false);
                resizeRowToContents(curRow);
            }
            if(visibleRowCntr == visibleRows)
                break;
        }
        else
        {
            if(!isRowHidden(curRow))
            {
                setRowHidden(curRow, true);
            }
        }
    }
    if(curRow)
        emit invisibleRows(true);
    else
        emit invisibleRows(false);

    while(visibleRowOffset < curRow)
    {
        setRowHidden(visibleRowOffset, true);
        visibleRowOffset++;
    }
    visibleRowOffset = curRow;
    scrollTo(model()->index(visibleRowOffsetHIGH, 3),QAbstractItemView::PositionAtBottom);
}

void MsgTableView::scrollFetchRows(int direction)
{
    unsigned int visibleRowOffsetShadow = visibleRowOffset;
    unsigned int visibleRowOffsetHIGHShadow = visibleRowOffsetHIGH;
    continuousScrolling = false;

    bottomEnd = false;
    topEnd = false;

    if(visibleRowOffset && (direction < 0 ))
    {
        while(visibleRowOffsetShadow)
        {
            if(isRowHidden(visibleRowOffsetShadow) && isLegit(visibleRowOffsetShadow))
                break;
            visibleRowOffsetShadow--;
        }

        while(visibleRowOffsetHIGHShadow)
        {
            if(!isRowHidden(visibleRowOffsetHIGHShadow))
                break;
            visibleRowOffsetHIGHShadow--;
        }

        if(isLegit(visibleRowOffsetShadow))
        {
            visibleRowOffset = visibleRowOffsetShadow;
            visibleRowOffsetHIGH =  visibleRowOffsetHIGHShadow;
            setRowHidden(visibleRowOffset, false);
            resizeRowToContents(visibleRowOffset);
            setRowHidden(visibleRowOffsetHIGH, true);
            visibleRowOffsetHIGH--;
        }else
        {
            bottomEnd = true;
        }

        scrollTo(model()->index(visibleRowOffset, 3),QAbstractItemView::PositionAtTop);
    }
    else if( ( direction > 0 ) &&
             ( visibleRowOffsetHIGH < this->model()->rowCount()))
    {
        while(visibleRowOffsetShadow)
        {
            if(!isRowHidden(visibleRowOffsetShadow))
                break;
            visibleRowOffsetShadow++;
        }
        unsigned int rowsInModel = model()->rowCount() -1;

        while(visibleRowOffsetHIGHShadow < rowsInModel)
        {
            if(isRowHidden(visibleRowOffsetHIGHShadow) && isLegit(visibleRowOffsetHIGHShadow))
                break;
            visibleRowOffsetHIGHShadow++;
        }

        if(isLegit(visibleRowOffsetHIGHShadow))
        {
            visibleRowOffset = visibleRowOffsetShadow;
            visibleRowOffsetHIGH = visibleRowOffsetHIGHShadow;
            setRowHidden(visibleRowOffset, true);
            setRowHidden(visibleRowOffsetHIGH, false);
            resizeRowToContents(visibleRowOffsetHIGH);
            if(!isRowHidden(rowsInModel))
            {
                continuousScrolling = true;
            }
        }
        else
        {
            topEnd = true;
            continuousScrolling = true;
        }
        scrollTo(model()->index(visibleRowOffsetHIGH, 3),QAbstractItemView::PositionAtBottom);

    } else
    {
        //emit scrollFetchRows(0);
    }
    qDebug() << "ContinuousScrolling :" << continuousScrolling;
}

void MsgTableView::scrollContinuousChange(bool enabled)
{
    qDebug() << "Continuous scrolling changed to:" << enabled;
    this->continuousScrolling = enabled;
}

void MsgTableView::changeIDFilterEnabled(bool enabled)
{
    this->idFilterEnabled = enabled;
    this->filterChanged();
}

void MsgTableView::changeCodeFilterEnabled(bool enabled)
{
    this->codeFilterEnabled = enabled;
    this->filterChanged();
}

void MsgTableView::changeTimestampFromFilterEnabled(bool enabled)
{
    this->timestampFromFilterEnabled = enabled;
    this->filterChanged();
}

void MsgTableView::changeTimestampToFilterEnabled(bool enabled)
{
    this->timestampToFilterEnabled = enabled;
    this->filterChanged();
}
