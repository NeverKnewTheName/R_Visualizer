#include "msgtableview.h"

#include <QDateTime>
#include <QDebug>

MsgTableView::MsgTableView(QWidget *parent) :
    QTableView(parent),
    visibleRows(VISIBLE_ROWS),
    visibleRowCntr(0),
    visibleRowOffset(0),
    continuousScrolling(true),
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

bool MsgTableView::isLegit(unsigned int rowNr) const
{
    bool isLegit = true;
    QDateTime timestamp = this->model()->index(rowNr, 0).data(Qt::UserRole+3).value<QDateTime>();
    unsigned int id = this->model()->index(rowNr, 1).data(Qt::UserRole+3).value<unsigned int>();
    unsigned int code = this->model()->index(rowNr, 2).data(Qt::UserRole+3).value<unsigned int>();

    if(idFilterEnabled)
        isLegit = isLegit && filterIDModel->containsID(id);
    if(codeFilterEnabled)
        isLegit = isLegit && filterCodeModel->containsCode(code);
    if(timestampFromFilterEnabled)
        isLegit = isLegit && filterTimestampModel->isValidTimestampFrom(timestamp);
    if(timestampToFilterEnabled)
        isLegit = isLegit && filterTimestampModel->isValidTimestampTo(timestamp);

    return isLegit;
}

void MsgTableView::reset()
{
    QTableView::reset();

    visibleRowCntr = 0;
    visibleRowOffset = 0;
}

void MsgTableView::rowAdded(unsigned int rowNr)
{
    // rows have been added!
    if(!isLegit(rowNr))
    {
        setRowHidden(rowNr, true);
    }
    else
    {
        visibleRowCntr++;
        if( visibleRowCntr > visibleRows)
        {
            while(isRowHidden(visibleRowOffset))
                visibleRowOffset++;
            setRowHidden(visibleRowOffset, true);
            visibleRowOffset++;
            visibleRowCntr--;
        }
        this->resizeRowToContents(rowNr);
    }
}

void MsgTableView::filterChanged()
{
    unsigned int curRow = model()->rowCount();
    qDebug() << "filterChanged - curRow" << curRow;
    int validRows = 0;
    //    while(curRow--)
    //    {
    //        if(isLegit(curRow))
    //        {
    ////            if((curRow > visibleRowOffset) && isRowHidden(curRow))
    //            if(isRowHidden(curRow))
    //            {
    //                visibleRowCntr++;
    //                if( visibleRowCntr > visibleRows)
    //                {
    //                    visibleRowCntr--;
    //                } else
    //                {
    //                    setRowHidden(curRow, false);
    //                }
    //            }
    //        }
    //        else
    //        {
    //            if(!isRowHidden(curRow))
    //            {
    //                visibleRowCntr--;
    //                setRowHidden(curRow, true);
    //            }
    //            if( visibleRowOffset && (visibleRowCntr < visibleRows))
    //            {
    //                while(visibleRowOffset && isRowHidden(visibleRowOffset))
    //                    visibleRowOffset--;
    //                if(!visibleRowOffset)
    //                    continue;
    //                setRowHidden(visibleRowOffset, false);
    //                visibleRowOffset--;
    //                visibleRowCntr++;
    //            }
    //        }
    //    }
    visibleRowCntr = 0;
    while(curRow)
    {
        curRow--;
        if(isLegit(curRow))
        {
            visibleRowCntr++;
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
    qDebug() << "after scan - curRow" << curRow;
    qDebug() << "visibleRowOffset" << visibleRowOffset;
    while(visibleRowOffset < curRow)
        setRowHidden(visibleRowOffset++, true);
    visibleRowOffset = curRow;

    qDebug() << "visibleRowCntr" << visibleRowCntr;
    qDebug() << "visibleRowOffset" << visibleRowOffset;
}

void MsgTableView::scrollFetchRows(int direction)
{
    if(visibleRowOffset && (direction < 0 ))
    {
        visibleRowOffset--;
        emit this->scrollFetchRows(+2);
    }
    else if( ( direction > 0 ) &&
             ( ( visibleRowOffset + visibleRows ) < this->model()->rowCount()))
    {
        visibleRowOffset++;
        emit this->scrollFetchRows(-2);
    }
}

void MsgTableView::scrollContinuousChange(bool enabled)
{
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
