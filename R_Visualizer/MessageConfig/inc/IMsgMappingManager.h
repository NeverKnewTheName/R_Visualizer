/**
 * @file IMsgMappingManager.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief General interface for message mappings
 */
#ifndef IMSGMAPPINGMANAGER_H
#define IMSGMAPPINGMANAGER_H

#include <QObject>

#include "IFileParsable.h"
#include "IUserRoleManageable.h"

class IPrettyMsg;

/**
 * @defgroup MsgMappingGroup Message Mappings
 * @ingroup MsgConfigGroup
 * 
 * Every class that is related to the Message Mappings
 * 
 * @{
 */

/**
 * @brief The IMsgMappingManager interface
 */
class IMsgMappingManager :
    public QObject,
    public IUserRoleManageable,
    public IFileParsable
{
public:
    IMsgMappingManager(
            QObject *parent = Q_NULLPTR
            ) :
        QObject(parent)
    {}
    virtual ~IMsgMappingManager(){}

    /**
     * @brief Prettifies the passed #IPrettyMsg and returns it as a reference
     */
    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const = 0;

signals:
    void sgnl_MappingManagerChanged(const IMsgMappingManager &mapping);

public slots:
    virtual void slt_ApplyRole(const UserRoleManagement::UserRole roleToApply)
    {
        applyUserRole(roleToApply);
    }

};

/**
 * @}
 */

#endif /* IMSGMAPPINGMANAGER_H */
