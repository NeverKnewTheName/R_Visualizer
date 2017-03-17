#ifndef IPLAINTEXTALIASMAPPING_H
#define IPLAINTEXTALIASMAPPING_H

#include <QString>

class IPlainTextAliasMapping
{
public:
    IPlainTextAliasMapping();
    virtual ~IPlainTextAliasMapping();

    QString getPlainTextAlias() const = 0;
    void setPlainTextAlias(const QString &plainTextAlias) = 0;

};

#endif /* IPLAINTEXTALIASMAPPING_H */
