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

class MessageConfig;
//class FileParser;

#include "filteridstore.h"
#include "filtercodestore.h"
#include "filtertimestampstore.h"

#include "IFileParsable.h"


namespace Ui {
class MessageFilter;
}

/**
 * \brief The #MessageFilter widget
 */
class MessageFilter : public QWidget//, public IFileParsable
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a #MessageFilter object
     * 
     * \param[in] msgConfig     Used for mapping #MsgIDType and #MsgCodeType to names and colors
     * \param[in] parent        The parent QWidget
     */
    explicit MessageFilter(
            const MessageConfig *msgConfig,
            QWidget *parent = 0
            );
    ~MessageFilter();

    /**
     * \brief Filters a #Msg according to all current filter settings
     */
    bool filterMsg(const Msg &msgToFilter) const;
    /**
     * \brief Filters a #Msg's ID according to the current ID filter settings
     */
    bool filterMsgID(const MsgIDType msgIDToFilter) const;
    /**
     * \brief Filters a #Msg's code according to the current code filter settings
     */
    bool filterMsgCode(const MsgCodeType msgCodeToFilter) const;
    /**
     * \brief Filters a #Msg's timestamp according to both timestamp filter settings
     */
    bool filterMsgTimestampSpan(const QDateTime &msgTimestamp) const;
    /**
     * \brief Filters a #Msg's timestamp according to the from timestamp filter
     */
    bool filterMsgTimestampFrom(const QDateTime &msgTimestamp) const;
    /**
     * \brief Filters a #Msg's timestamp according to the to timestamp filter
     */
    bool filterMsgTimestampTo(const QDateTime &msgTimestamp) const;

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

    //void accept(FileParser *visitor);

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
     * \brief This signal is emitted when the Code filter is enabled/disabled
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

    void on_filterIDSaveBtn_clicked();

    void on_filterIDLoadBtn_clicked();

    void on_filterCodeSaveBtn_clicked();

    void on_filterCodeLoadBtn_clicked();

    void on_filterTimestampSaveBtn_clicked();

    void on_filterTimestampLoadBtn_clicked();

private:
    /**
     * \brief Initializes the ID filter
     */
    void initFilterIDListView();
    /**
     * \brief Initializes the Code filter
     */
    void initFilterCodeListView();
    /**
     * \brief Initializes the Timestamp filter
     */
    void initFilterTimestamp();

    //void saveIDFilter(const QString &pathToFile, FileParser *saveFileParser);
    //void saveCodeFilter(const QString &pathToFile, FileParser *saveFileParser);
    //void saveTimestampFilter(const QString &pathToFile, FileParser *saveFileParser);
    //void loadIDFilter(const QString &pathToFile, FileParser *openFileParser);
    //void loadCodeFilter(const QString &pathToFile, FileParser *openFileParser);
    //void loadTimestampFilter(const QString &pathToFile, FileParser *openFileParser);

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
    FilterTimestampStore filterTimestampModel;

    const MessageConfig *msgConfig;
};

#endif // MESSAGEFILTER_H
