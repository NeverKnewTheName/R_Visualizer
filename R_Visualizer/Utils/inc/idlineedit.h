/**
 * @file idlineedit.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief Provides a QLineEdit specific for entering messages ids
 */
#ifndef IDLINEEDIT_H
#define IDLINEEDIT_H

#include <QLineEdit>
#include <QMetaObject>
#include <QCompleter>

#include "MsgIDType.h"

class IMsgIDMapping;

/**
 * @brief The IDLineEdit
 */
class IDLineEdit : public QLineEdit
{
public:
    /**
     * @brief Constructs a default #IDLineEdit object with not completion and
     * no alias mapping capabilities
     * 
     * \note To get the full functionality set a MsgIDMapping with
     * #setMsgIDMapping and setCompleter.
     */
    IDLineEdit( QWidget *parent = Q_NULLPTR);

    /**
     * @brief Constructs a fully functional #IDLineEdit object with
     * autocomplettion and alias mapping
     * 
     * \note Use a QCompleter that has its model set to a #IMsgIDMappingModel
     * that is related to the #msgIDMapping's #IMsgIDMappingStore
     */
    IDLineEdit(
            const IMsgIDMapping *msgIDMapping,
            QCompleter *msgIDAliasCompleter = Q_NULLPTR,
            QWidget *parent = Q_NULLPTR
            );
    /**
     * @brief Destructs the #IDLineEdit object
     */
    virtual ~IDLineEdit();

    /**
     * @brief Sets the #IMsgIDMapping for this #IDLineEdit
     * 
     * @note Sets up the connections automatically
     */
    void setMsgIDMapping(const IMsgIDMapping *msgIDMapping);

    /**
     * @brief Returns the parsed #MsgIDType from the #IDLineEdit
     * 
     * The #IDLineEdit is capable of converting strings to #MsgIDType objects.
     * The strings must either contain a numerical ID value (hex or dec) or an
     * alias that has been set in the passed #IMsgIDMapping.
     */
    MsgIDType getMsgID() const;

private:
    /**
     * @brief The #IMsgIDMapping that is used to convert aliases to #MsgIDType
     * 
     * With the help of the msgIDMapping text aliases are converted to
     * #MsgIDTypes. Additionally, the background color of the #IDLineEdit is
     * adapted to the color representation for the text alias, if available
     */
    const IMsgIDMapping *msgIDMapping;
    /* QCompleter *msgIDAliasCompleter; */
    /**
     * @brief Connection object that holds the connection between the passed
     * #IMsgIDMapping and this #IDLineEdit
     * 
     * The connection is stored for the case when the #IMsgIDMapping is
     * exchanged and the previous connection has to be disconnected.
     */
    QMetaObject::Connection colorizeLineEditConnection;

    /**
     * @brief Connectes the current #IMsgIDMapping to this #IDLineEdit
     * 
     * The connection connects this #IDLineEdit's TextChanged slot to a lambda
     * expression that parses the input to an alias and then sets the
     * background color of this #IDLineEdit to the corresponding color
     * representation, if available. If no suitable color representation is
     * found the background color defaults to white.
     */
    void connectMsgIDMapping();
    virtual MsgIDType convertTextToMsgID(const QString &text) const;
    /* void msgIDMappingChanged(); */
};

#endif /* IDLINEEDIT_H */
