/**
 * @file IMsgMapping.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief General interface for message mappings
 */
#ifndef IMSGMAPPING_H
#define IMSGMAPPING_H

#include "IFileParsable.h"
#include "IUserRoleManageable.h"

class IPrettyMsg;

/**
 * @brief The IMsgMapping interface
 */
class IMsgMapping : public QObject, public IUserRoleManageable, public IFileParsable
{
public:
    virtual ~IMsgMapping(){}

    /**
     * @brief Prettifies the passed #IPrettyMsg and returns it as a reference
     */
    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const = 0;

signals:
    void sgnl_MappingChanged(const IMsgMapping &mapping);

public slots:
    virtual void slt_ApplyRole(const UserRoleManagement::UserRole roleToApply)
    {
        applyUserRole(roleToApply);
    }

};

#endif /* IMSGMAPPING_H */
