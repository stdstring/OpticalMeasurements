#pragma once

#include <QObject>
#include <QString>

#include "ILogger.h"

namespace CalcApp
{

class NullLogger : public ILogger
{
public:
    explicit NullLogger(LogLevel level, QObject *parent = nullptr) : ILogger(level, parent) {}

    virtual void WriteDebug(QString const &message) override {}
    virtual void WriteDebug(LoggerCategory const &category, QString const &message) override {}
    /*virtual void WriteDebugFormat(QString const &format, ...) override {}
    virtual void WriteDebugFormat(LoggerCategory const &category, QString const &format, ...) override {}*/
    virtual void WriteInfo(QString const &message) override {}
    virtual void WriteInfo(LoggerCategory const &category, QString const &message) override {}
    /*virtual void WriteInfoFormat(QString const &format, ...) override {}
    virtual void WriteInfoFormat(LoggerCategory const &category, QString const &format, ...) override {}*/
    virtual void WriteWarning(QString const &message) override {}
    virtual void WriteWarning(LoggerCategory const &category, QString const &message) override {}
    /*virtual void WriteWarningFormat(QString const &format, ...) override {}
    virtual void WriteWarningFormat(LoggerCategory const &category, QString const &format, ...) override {}*/
    virtual void WriteError(QString const &message) override {}
    virtual void WriteError(LoggerCategory const &category, QString const &message) override {}
    /*virtual void WriteErrorFormat(QString const &format, ...) override {}
    virtual void WriteErrorFormat(LoggerCategory const &category, QString const &format, ...) override {}*/
    /*virtual void WriteCritical(QString const &message) override {}
    virtual void WriteCritical(LoggerCategory const &category, QString const &message) override {}
    virtual void WriteCriticalFormat(QString const &format, ...) override {}
    virtual void WriteCriticalFormat(LoggerCategory const &category, QString const &format, ...) override {}*/
};

}
