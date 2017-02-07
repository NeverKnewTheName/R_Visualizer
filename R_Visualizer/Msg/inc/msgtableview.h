/**
 * \file msgtableview.h
 * \author Christian Neuberger
 * \date 2017-02-06
 * 
 * \brief A TableView for the #MessageStream that displays #Msg
 */
#ifndef MSGTABLEVIEW_H
#define MSGTABLEVIEW_H

#include "filteridstore.h"
#include "filtercodestore.h"
#include "filtertimestampstore.h"

#include <QTableView>

#define VISIBLE_ROWS 200u

/**
 * \brief The #MsgTableView class provides a TableView to display #Msg
 * 
 * The class limits the number of #Msg that are shown for efficiency.
 * If the TableView is scrolled the respective #Msg are automatically loaded
 * and displayed.
 */
class MsgTableView : public QTableView
{
    Q_OBJECT
public:
    /**
     * \brief Constructs a new #MsgTableView
     */
    explicit MsgTableView(QWidget *parent = Q_NULLPTR);

    /**
     * \brief Returns the number of visible rows
     */
    unsigned int getVisibleRows() const;
    /**
     * \brief Sets the number of visible rows
     */
    void setVisibleRows(unsigned int value);

    FilterIDStore *getFilterIDModel() const;
    void setFilterIDModel(FilterIDStore *value);

    FilterCodeStore *getFilterCodeModel() const;
    void setFilterCodeModel(FilterCodeStore *value);

    FilterTimestampStore *getFilterTimestampModel() const;
    void setFilterTimestampModel(FilterTimestampStore *value);

    bool isAtBottomEnd();
    bool isAtTopEnd();

private:
    bool isLegit(unsigned int rowNr) const;

    unsigned int visibleRows;
    unsigned int visibleRowCntr;
    unsigned int visibleRowOffset;
    unsigned int visibleRowOffsetHIGH;

    bool continuousScrolling;
    bool bottomEnd;
    bool topEnd;

    FilterIDStore *filterIDModel;
    FilterCodeStore *filterCodeModel;
    FilterTimestampStore *filterTimestampModel;

    bool idFilterEnabled;
    bool codeFilterEnabled;
    bool timestampFromFilterEnabled;
    bool timestampToFilterEnabled;

signals:
    void scrollRowsFetched(int direction);
    void invisibleRows(bool areThereInvisibleRows);

public slots:
    void reset();
    void rowAdded(unsigned int rowNr);
    void filterChanged();
    void scrollFetchRows(int direction);
    void scrollContinuousChange(bool enabled);
    void changeIDFilterEnabled(bool enabled);
    void changeCodeFilterEnabled(bool enabled);
    void changeTimestampFromFilterEnabled(bool enabled);
    void changeTimestampToFilterEnabled(bool enabled);

protected slots:
    void columnResized(int column, int oldWidth, int newWidth);
};

#endif // MSGTABLEVIEW_H
