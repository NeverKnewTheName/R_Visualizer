#ifndef IPLAINTEXTALIASMAPPING_H
#define IPLAINTEXTALIASMAPPING_H

#include <QString>

class IPlainTextAliasMapping
{
public:
    virtual ~IPlainTextAliasMapping(){}

    virtual QString getPlainTextAlias() const = 0;
    virtual void setPlainTextAlias(const QString &plainTextAlias) = 0;
};

#endif /* IPLAINTEXTALIASMAPPING_H */
