/**
 * \file IMsgDataMapping.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for a message data mapping
 */
#ifndef IMSGDATAMAPPING_H
#define IMSGDATAMAPPING_H

#include <QString>
#include <QColor>

#include "IMsg.h"
#include "IFileParsable.h"

class IMsgDataFormatter;

/**
 * @addtogroup MsgDataMappingGroup
 * 
 * @{
 */


/**
 * \brief The IMsgDataMapping interface
 */
class IMsgDataMapping : public IFileParsable
{
public:
    virtual ~IMsgDataMapping(){}

    virtual IMsgDataMapping *cloneMsgDataMapping() const = 0;

    virtual MsgIDType getMsgID() const = 0;
    virtual void setMsgID(const MsgIDType &id) = 0;

    virtual MsgCodeType getMsgCode() const = 0;
    virtual void setMsgCode(const MsgCodeType &code) = 0;

    virtual QString getMsgDataFormatString() const = 0;
    virtual void  setMsgDataFormatString(
            const QString &msgDataFormatString
            ) = 0;

    virtual QColor getMsgDataDefaultColor() const = 0;
    virtual void setMsgDataDefaultColor(
            const QColor &defaultColor
            ) = 0;

    virtual QSharedPointer<IMsgDataFormatter> getMsgDataFormatter() const = 0;
    virtual void setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter) = 0;

    virtual QString parseMsgData(const IMsg &msg) const = 0;
};


/**
 * @brief CRTP copy helper for #IMsgDataMapping
 */
template<class Derived>
class MsgDataMappingCRTPHelper : public IMsgDataMapping
{
public:
    virtual ~MsgDataMappingCRTPHelper(){}
    virtual IMsgDataMapping *cloneMsgDataMapping() const
    {
        return new Derived(static_cast<const Derived&>(*this));
    }
};

/**
 * @}
 */

#endif /* IMSGDATAMAPPING_H */
