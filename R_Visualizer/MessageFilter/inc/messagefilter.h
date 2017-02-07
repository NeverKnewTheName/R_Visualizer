#ifndef MESSAGEFILTER_H
#define MESSAGEFILTER_H

#include <QWidget>

#include "filteridstore.h"
#include "filtercodestore.h"
#include "filtertimestampstore.h"


namespace Ui {
class MessageFilter;
}

class MessageFilter : public QWidget
{
    Q_OBJECT

public:
    explicit MessageFilter(
            const IDModel &idModel,
            const MsgTypeModel &msgTypeModel,
            QWidget *parent = 0
            );
    ~MessageFilter();

private:
    void initFilterIDListView(const IDModel &idModel);
    void initFilterCodeListView(const MsgTypeModel &msgTypeModel);

    Ui::MessageFilter *ui;
    FilterIDStore filterIDModel;
    FilterCodeStore filterCodeModel;
    FilterTimestampStore filterTimestampStore;
};

#endif // MESSAGEFILTER_H
