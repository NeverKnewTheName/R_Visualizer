/**
 * \file messagefilter.h
 * \author Christian Neuberger
 * \date 2017-02-08
 * 
 * \brief Filter widget for #Msg in the #MessageStream
 */
#ifndef MESSAGEFILTER_H
#define MESSAGEFILTER_H

#include <QWidget>

#include "filteridstore.h"
#include "filtercodestore.h"
#include "filtertimestampstore.h"


namespace Ui {
class MessageFilter;
}

/**
 * \brief The #MessageFilter widget
 */
class MessageFilter : public QWidget
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a #MessageFilter object
     * 
     * \param[in] idModel The #IDModel that is used for autocompletion and name to #MsgIDType resolution
     * \param[in] msgTypeModel The #MsgTypeModel that is used for autocompletion and name to #MsgCodeType resolution
     */
    explicit MessageFilter(
            const IDModel &idModel,
            const MsgTypeModel &msgTypeModel,
            QWidget *parent = 0
            );
    ~MessageFilter();

    /**
     * \brief Returns a const reference the filterIDModel
     */
    const FilterIDStore &getFilterIDModel() const;
    /**
     * \brief Returns a const reference to the filterCodeModel
     */
    const FilterCodeStore &getFilterCodeModel() const;
    /**
     * \brief Returns a const reference to the filterTimestampModel
     */
    const FilterTimestampStore &getFilterTimestampModel() const;

signals:
    /**
     * \brief This signal is emitted when the ID filter is enabled/disabled
     */
    void sgnl_IDFilterEnabled(bool enabled);
    /**
     * \brief This signal is emitted every time an ID is added to the ID filter
     */
    void sgnl_IDAddedToFilter();
    /**
     * \brief This signal is emitted every time an ID is removed from the ID filter
     */
    void sgnl_IDRemovedFromFilter();
    /**
     * \brief This signal is emitted when teh Code filter is enabled/disabled
     */
    void sgnl_CodeFilterEnabled(bool enable);
    /**
     * \brief This signal is emitted every time a code is added to the Code filter
     */
    void sgnl_CodeAddedToFilter();
    /**
     * \brief This signal is emitted every time a code is removed from the code filter
     */
    void sgnl_CodeRemovedFromFilter();
    /**
     * \brief This signal is emitted when the Timestap TO filter is enabled/disabled
     */
    void sgnl_TimestampFilterToEnabled(bool enable);
    /**
     * \brief This signal is emitted every time the Timestamp TO filter is changed
     */
    void sgnl_TimestampToChanged();
    /**
     * \brief This signal is emitted when the Timestamp FROM filter is enabled/disabled
     */
    void sgnl_TimestampFilterFromEnabled(bool enable);
    /**
     * \brief This signal is emitted every time the Timestamp FROM filter is changed
     */
    void sgnl_TimestampFromChanged();

private slots:
    /**
     * \brief This slot is called when the value of the enabled checkbox for the ID filter is toggled
     */
    void on_enableIDFilterCheckBox_toggled(bool checked);
    /**
     * \brief This slot is called when the add button for the ID filter is pushed
     */
    void on_addFilterIDPushButton_clicked();
    /**
     * \brief This slot is called when the remove button for the ID filter is pushed
     */
    void on_rmvFilterIDPushButton_clicked();
    /**
     * \brief This slot is called when the value of the enabled checkbox for the code filter is toggled
     */
    void on_enableCodeFilterCheckBox_toggled(bool checked);
    /**
     * \brief This slot is called when the add button for the Code filter is pushed
     */
    void on_addFilterCodePushButton_clicked();
    /**
     * \brief This slot is called when the remove button for the Code filter is pushed
     */
    void on_rmvFilterCodePushButton_clicked();
    /**
     * \brief This slot is called when the enabled checkbox for the Timestamp TO filter is toggled
     */
    void on_enableTimestampFromFilterCheckBox_toggled(bool checked);
    /**
     * \brief This slot is called when the Timestamp TO filter value is changed
     * 
     * This does automatically adjust the Timestamp FROM filter value so that these two
     * filters always form a valid range.
     */
    void on_filterTimeStampFromDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    /**
     * \brief This slot is called when the enabled checkbox for the Timestamp FROM filter is toggled
     */
    void on_enableTimestampToFilterCheckBox_toggled(bool checked);
    /**
     * \brief This slot is called when the Timestamp FROM filter value is changed
     * 
     * This does automatically adjust the Timestamp TO filter value so that these two
     * filters always form a valid range.
     */
    void on_filterTimeStampToDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void slt_timestampToChanged(const QDateTime &newFromDateTime);
    void slt_timestampFromChanged(const QDateTime &newToDateTime);

    /**
     * \brief This slot is called when the ID Filter add ID dialog commits its content
     * 
     * This slot is responsible for adding the idToCommit to the #filterIDModel
     */
    void filterIDCommit(const MsgIDType idToCommit);
    /**
     * \brief This slot is called when the Code Filter add Code dialog commits its content
     * 
     * This slot is responsible for adding the codeToCommit to the #filterCodeModel
     */
    void filterCodeCommit(const MsgCodeType codeToCommit);

private:
    /**
     * \brief Initializes the ID filter
     */
    void initFilterIDListView(const IDModel &idModel);
    /**
     * \brief Initializes the Code filter
     */
    void initFilterCodeListView(const MsgTypeModel &msgTypeModel);
    /**
     * \brief Initializes the Timestamp filter
     */
    void initFilterTimestamp();

    Ui::MessageFilter *ui;
    /**
     * \brief Contains the IDs to filter for by the ID filter
     */
    FilterIDStore filterIDModel;
    /**
     * \brief Contains the Codes to filter for by the Code filter
     */
    FilterCodeStore filterCodeModel;
    /**
     * \brief Contains the Timestamps to filter for by the Timestamp filter
     */
    FilterTimestampStore filterTimestampStore;
};

#endif // MESSAGEFILTER_H
