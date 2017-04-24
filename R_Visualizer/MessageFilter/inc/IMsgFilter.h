/**
 * @file IMsgFilter.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Provides an interface for message filters
 */
#ifndef IMSGFILTER_H
#define IMSGFILTER_H

#include "IFilter.h"

class IMsg;

/**
 * @brief The #IMsgFilter interface
 */
class IMsgFilter : public IFilter
{
    Q_OBJECT
public:
    IMsgFilter(QObject * parent = Q_NULLPTR) : IFilter(parent){}
    virtual ~IMsgFilter(){}

    /**
     * @brief Filters an #IMsg according to the current filter configuration and
     * filter criteria
     */
    virtual bool filterMessage(const IMsg &msgToFilter) const = 0;

signals:
    void sgnl_MsgFilterChanged(const IMsgFilter &filterThatHasChanged);

public slots:
};

#endif /* IFILTER_H */
