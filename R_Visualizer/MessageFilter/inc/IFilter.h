/**
 * @file IFilter.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Provides an interface for message filters
 */
#ifndef IFILTER_H
#define IFILTER_H

/**
 * @brief The #IFilter interface
 */
class IFilter
{
public:
    virtual ~IFilter(){}

    /**
     * @brief Enables or disables the filter according to the passed enable
     * value
     */
    virtual void enableFilter(const bool enable) = 0;
    /**
     * @brief Query the current enable state of the filter
     */
    virtual bool isFilterEnabled() const = 0;

    /**
     * @brief Inverts the filter according to the invert value
     */
    virtual void invertFilter(const bool invert) = 0;
    /**
     * @brief Queries the current invert state of the filter
     */
    virtual bool isFilterInverted() const = 0;

signals:
    /**
     * @brief This signal is emitted when the enable state of the filter is
     * changed
     */
    virtual void sgnl_filterEnabled(const bool enabled) = 0;
    /**
     * @brief This signal is emitted when the invert state of the filter is
     * changed
     */
    virtual void sgnl_filterInverted(const bool inverted) = 0;
    /**
     * @brief This signal is emitted when the filter changes in general
     * 
     * @warning This signal is also emitted when the filter's enable or invert
     * state changes! Keep this in mind when connecting the signals to slots.
     */
    virtual void sgnl_filterChanged() = 0;

public slots:
    /**
     * @brief Slot that changes the filter's enable state according to the
     * enable value
     */
    virtual void slt_enableFilter(const bool enable) = 0;
    /**
     * @brief Slot that changes the filter's invert state according to the
     * invert value
     */
    virtual void slt_invertFilter(const bool invert) = 0;
};

#endif /* IFILTER_H */
