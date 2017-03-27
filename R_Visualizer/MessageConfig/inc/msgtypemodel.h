/**
 * \file msgtypemodel.h
 * \author Christian Neuberger
 * \date 2017-02-06
 * 
 * \brief Model to hold Code to name, color, and message data parser mapping for #Msg
 */
#ifndef MSGTYPEMODEL_H
#define MSGTYPEMODEL_H


#include <QAbstractTableModel>
#include <QVector>
#include <QStyleOptionViewItem>
#include <QCompleter>

class FileParser;

#include "Msg.h"
#include "msgtyperep.h"
#include "IFileParsable.h"

/**
 * \brief The #MsgTypeModel class provides a model to hold Code to name, color, and message data parser mappings for #Msg
 */
class MsgTypeModel : public QAbstractTableModel, public IFileParsable
{
    Q_OBJECT

public:
    /**
     * \brief Enumeration of the header columns for the #MsgTypeModel
     */
    enum HeaderCols
    {
        COL_CODE, //!< Column in which the #MsgCodeType is shown
        COL_CODENAME, //!< Column in which the name mapping is shown
        COL_MESSAGEFORMAT, //!< Column in which the message data parser code is shown
        COL_COLOR, //!< Column in which the color mapping is shown
        COL_NR_OF_COLS //!< Number of header colums for the #MsgTypeModel
    };

    /**
     * \brief Constructs an empty #MsgTypeModel
     */
    MsgTypeModel(QObject *parent = 0);

    /**
     * \brief Returns the current number of rows/mappings
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * \brief Returns the columns for a view to dispaly
     * 
     * The default colums include:
     * - The MsgCode
     * - An associated name
     * - An associated message data parser code
     * - An associated color
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * \brief Retrieves data from the #MsgTypeModel for the given index according to the given role
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    /**
     * \brief Sets the data for a mapping at the given index with to the given value according to the given role
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    /**
     * \brief Returns the HeaderData for the given section, orientation, and role
     * 
     * Per default the #IDModel has the following sections:
     * - The MsgCode
     * - A Name mapping
     * - A message data parser code
     * - A Color mapping
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    /**
     * \brief Removes count rows/mappings starting at row
     */
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    /**
     * \brief Removes a single row/mapping at row
     */
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    /**
     * \brief Returns the valid flags for a given index
     * 
     * Per default items in the #MsgTypeModel are editable, selectable, and focuseable.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    /**
     * \brief Adds a #MsgTypeRep mapping to the #MsgTypeModel
     */
    void add(const MsgTypeRep &msgTypeRep);

    /**
     * \brief Returns the #MsgTypeRep that is stored in the model for the given code
     * 
     * Queries the model for the provided code. 
     * If there is an existing #MsgTypeRep associated with the code in the model,
     * it is returned.
     * If there is no existing #MsgTypeRep associated with the code in the model,
     * a new default #MsgTypeRep for that code is returned.
     */
    MsgTypeRep getMsgTypeRepToCode(const MsgCodeType code) const;
    /**
     * \brief Clears the whole #MsgTypeModel for a fresh start
     */
    void clear();

    const int size() const;

    const MsgTypeRep &at(const int index) const;


    /**
     * \brief Returns whether a given #MsgCodeType is contained in the #MsgTypeModel
     */
    bool contains(const MsgCodeType MsgCode) const;
    /**
     * \brief Returns the name mapping to a given #MsgCodeType
     */
    QString getNameToCode(const MsgCodeType code) const;
    /**
     * \brief Returns the #MsgCodeType associated with a given name
     */
    MsgCodeType getCodeToName(const QString &name) const;
    /**
     * \brief Returns the message data parser code as a string to a given code
     */
    QString getMessageToCode(const MsgCodeType code) const;
    /**
     * \brief Returns the color mapping to a given #MsgCodeType
     */
    QColor getColorToCode(const MsgCodeType code) const;
    /**
     * \brief Returns the number of lines of the message data parser code
     * 
     * This function provides a rough estimate about the size of the
     * message that is the result of parsing the message data with the
     * message data parser code.
     */
    int getNrLinesToCode(const MsgCodeType code);

    /**
     * \brief Returns all code names that are contained in the #MsgTypeModel
     */
    QStringList getAllCodeNames() const;

    /**
     * \brief Parses the contents of the #MsgTypeModel to a JSON format QByteArray
     */
    QByteArray ParseToJson() const;
    /**
     * \brief Parses the contents contents of a QByteArray that was previously saved by the #MsgTypeModel into the #MsgTypeModel
     */
    void ParseFromJson(const QByteArray &jsonFile);



    /**
     * \brief Paint a #Msg according to the code and the mappings contained in this #MsgTypeModel
     */
    void paintMsgTypeRep(QPainter *painter, const QStyleOptionViewItem &option, const MsgCodeType code, Msg &msg) const;

    QCompleter *createMsgTypeCompleter(QObject *parent = Q_NULLPTR) const;

    void accept(FileParser *visitor);

private:
    /**
     * \brief QVector containing all stored #MsgCodeTypes for which mappings exist in the #MsgTypeModel
     */
    QVector<MsgCodeType> codeStore;
    /**
     * \brief QHash that contains the respective #MsgCodeType to #MsgTypeRep mappings
     */
    QHash<MsgCodeType, MsgTypeRep> msgTypePropStore;

signals:
    /**
     * \brief The #internalModelChanged signal is emitted every time the data in the #MsgTypeModel changes
     */
    void internalModelChanged();
    void sgnl_MsgTypeRepAdded(const MsgTypeRep &newMsgTypeRep);
    void sgnl_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep);
    void sgnl_MsgTypeRepRemoved(const MsgCodeType relatedCode);
};

#endif // MSGTYPEMODEL_H
