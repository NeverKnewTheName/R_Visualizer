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
    return visibleRowOffset == 0;
}

bool MsgTableView::isAtTopEnd()
{
    return !isRowHidden(model()->rowCount()-1);
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
    if(!continuousScrolling || !isLegit(rowNr))
    {
        setRowHidden(rowNr, true);
    }
    else
    {
        visibleRowCntr++;
        visibleRowOffsetHIGH++;
        if( visibleRowCntr > visibleRows)
        {
            emit invisibleRows(true);
            while(isRowHidden(visibleRowOffset))
                visibleRowOffset++;
            setRowHidden(visibleRowOffset, true);
            //setRowHidden(indexAt(this->rect().topLeft()).row(), true);
            visibleRowOffset++;
            visibleRowCntr--;
        }else
        {
            emit invisibleRows(false);
        }
        this->resizeRowToContents(rowNr);
        scrollTo(model()->index(rowNr, 0),QAbstractItemView::PositionAtBottom);
    }
}

void MsgTableView::filterChanged()
{
    unsigned int curRow = model()->rowCount();
//    qDebug() << "filterChanged - curRow" << curRow;

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
//    qDebug() << "after scan - curRow" << curRow;
//    qDebug() << "visibleRowOffset" << visibleRowOffset;
    if(curRow)
        emit invisibleRows(true);
    else
        emit invisibleRows(false);

    while(visibleRowOffset < curRow)
    {
        //if(!isRowHidden(visibleRowOffset))
            setRowHidden(visibleRowOffset++, true);
        //visibleRowOffset++;
    }
    visibleRowOffset = curRow;

//    qDebug() << "visibleRowCntr" << visibleRowCntr;
//    qDebug() << "visibleRowOffset" << visibleRowOffset;
}

void MsgTableView::scrollFetchRows(int direction)
{
//    qDebug() << __PRETTY_FUNCTION__;
//    qDebug() << "VisibleRowOffset" << visibleRowOffset;
    unsigned int svdOffset = visibleRowOffset;
    continuousScrolling = false;
    if(visibleRowOffset && (direction < 0 ))
    {
//        qDebug() << "negative scroll";
        //setRowHidden(rowAt(height()), true);
        //visibleRowOffset = rowAt(0);
        while(visibleRowOffset)
        {
            if(isRowHidden(visibleRowOffset) && isLegit(visibleRowOffset))
                break;
            visibleRowOffset--;
        }
        while(visibleRowOffsetHIGH)
        {
            if(!isRowHidden(visibleRowOffsetHIGH))
                break;
            visibleRowOffsetHIGH--;
        }
//        qDebug() << "Row to show:" << visibleRowOffset;
//        qDebug() << "Row to hide:" << visibleRowOffsetHIGH; //svdOffset;
        setRowHidden(visibleRowOffset, false);
        resizeRowToContents(visibleRowOffset);
//        setRowHidden(svdOffset, true);
        setRowHidden(visibleRowOffsetHIGH--, true);
        //emit scrollFetchRows(+2);
    }
    else if( ( direction > 0 ) &&
             ( visibleRowOffsetHIGH < this->model()->rowCount()))
    {
//        qDebug() << "positive scroll";
        svdOffset += visibleRowCntr;
        while(visibleRowOffset)
        {
            if(!isRowHidden(visibleRowOffset))
                break;
            visibleRowOffset++;
        }
//        qDebug() << "Model RowCount" << model()->rowCount();
        unsigned int rowsInModel = model()->rowCount() -1;
//        while(svdOffset < rowsInModel)
//        {
//            if(isRowHidden(svdOffset) && isLegit(svdOffset))
//                break;
//            svdOffset++;
//        }
        while(visibleRowOffsetHIGH < rowsInModel)
        {
            if(isRowHidden(visibleRowOffsetHIGH) && isLegit(visibleRowOffsetHIGH))
                break;
            visibleRowOffsetHIGH++;
        }
//        qDebug() << "Row to hide:" << visibleRowOffset;
//        qDebug() << "Row to show:" << visibleRowOffsetHIGH;
        setRowHidden(visibleRowOffset, true);
        setRowHidden(visibleRowOffsetHIGH, false);
        resizeRowToContents(visibleRowOffsetHIGH);
        if(!isRowHidden(rowsInModel))
            continuousScrolling = true;
        //visibleRowOffset++;
        //emit scrollFetchRows(-2);
    } else
    {
        //emit scrollFetchRows(0);
    }
    //this->scrollTo(model()->index(svdOffset, 0));
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
