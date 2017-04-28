/**
 * @file AbstractMsgFieldLineEdit.h
 * @author Christian Neuberger
 * @date date
 *
 * @brief Abstract base class for Message Field Line edits
 *
 */
#ifndef ABSTRACTMSGFIELDLINEEDIT_H
#define ABSTRACTMSGFIELDLINEEDIT_H

#include <QString>

/**
 * @defgroup MessageWidgetsGroup Message Widgets
 * @ingroup MessageGroup
 *
 * @{
 */

/**
 * @brief The AbstractMsgFieldLineEdit
 */
class AbstractMsgFieldLineEdit
{
public:
    AbstractMsgFieldLineEdit();

    virtual int convertStringToNumber(
            const QString &number
            ) const;
};

/**
 * @}
 */

#endif // ABSTRACTMSGFIELDLINEEDIT_H
