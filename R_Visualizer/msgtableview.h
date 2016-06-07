#ifndef MSGTABLEVIEW_H
#define MSGTABLEVIEW_H

#include "MessageConfig/filteridstore.h"
#include "MessageConfig/filtercodestore.h"
#include "MessageConfig/filtertimestampstore.h"

#include <QTableView>

#define VISIBLE_ROWS 100u

class MsgTableView : public QTableView
{
    Q_OBJECT
public:
    explicit MsgTableView(QWidget *parent = Q_NULLPTR);

    unsigned int getVisibleRows() const;
    void setVisibleRows(unsigned int value);

    FilterIDStore *getFilterIDModel() const;
    void setFilterIDModel(FilterIDStore *value);

    FilterCodeStore *getFilterCodeModel() const;
    void setFilterCodeModel(FilterCodeStore *value);

    FilterTimestampStore *getFilterTimestampModel() const;
    void setFilterTimestampModel(FilterTimestampStore *value);

private:
    bool isLegit(unsigned int rowNr) const;

    unsigned int visibleRows;
    unsigned int visibleRowCntr;
    unsigned int visibleRowOffset;
    bool continuousScrolling;
    FilterIDStore *filterIDModel;
    FilterCodeStore *filterCodeModel;
    FilterTimestampStore *filterTimestampModel;
    bool idFilterEnabled;
    bool codeFilterEnabled;
    bool timestampFromFilterEnabled;
    bool timestampToFilterEnabled;

signals:
    void scrollRowsFetched(int direction);

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
};

#endif // MSGTABLEVIEW_H
