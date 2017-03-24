/**
 * \file IPlainTextAliasMapping.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for classes that have or provide a plain-text
 * alias representation
 */
#ifndef IPLAINTEXTALIASMAPPING_H
#define IPLAINTEXTALIASMAPPING_H

#include <QString>

/**
 * \brief The IPlainTextAliasMapping interface
 */
class IPlainTextAliasMapping
{
public:
    virtual ~IPlainTextAliasMapping(){}

    virtual QString getPlainTextAlias() const = 0;
    virtual void setPlainTextAlias(const QString &plainTextAlias) = 0;
};

#endif /* IPLAINTEXTALIASMAPPING_H */
