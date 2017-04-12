#pragma once

#include <QString>

namespace CalcApp
{

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class LoggerCategory
{
};

class ILogger
{
public:
    LogLevel GetLogLevel() const;
    void SetLogLevel(LogLevel level);
    void WriteDebug(QString const &message);
    void WriteDebug(LoggerCategory const &category, QString const &message);
    void WriteDebugFormat(QString const &format, ...);
    void WriteDebugFormat(LoggerCategory const &category, QString const &format, ...);
    void WriteInfo(QString const &message);
    void WriteInfo(LoggerCategory const &category, QString const &message);
    void WriteInfoFormat(QString const &message, ...);
    void WriteInfoFormat(LoggerCategory const &category, QString const &message, ...);
    void WriteWarning(QString const &message);
    void WriteWarning(LoggerCategory const &category, QString const &message);
    void WriteWarningFormat(QString const &message, ...);
    void WriteWarningFormat(LoggerCategory const &category, QString const &message, ...);
    void WriteError(QString const &message);
    void WriteError(LoggerCategory const &category, QString const &message);
    void WriteErrorFormat(QString const &message, ...);
    void WriteErrorFormat(LoggerCategory const &category, QString const &message, ...);
    void WriteCritical(QString const &message);
    void WriteCritical(LoggerCategory const &category, QString const &message);
    void WriteCriticalFormat(QString const &message, ...);
    void WriteCriticalFormat(LoggerCategory const &category, QString const &message, ...);
};

}

