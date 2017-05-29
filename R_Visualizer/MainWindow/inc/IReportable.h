#ifndef IREPORTABLE_H
#define IREPORTABLE_H

#include <QMetaType>

class IReportable
{
public:
    virtual ~IReportable(){}

signals:
    virtual void sgnl_ReportError(const QString &errorString) = 0;
    virtual void sgnl_ReportWarning(const QString &warningString) = 0;
    virtual void sgnl_ReportInfo(const QString &infoString) = 0;
};

Q_DECLARE_INTERFACE(IReportable, "IReportable");

#endif /* IREPORTABLE_H */
