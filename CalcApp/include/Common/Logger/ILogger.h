#pragma once

#include <QObject>
#include <QString>

namespace CalcApp
{

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class LoggerCategory
{
};

class ILogger : public QObject
{
public:
    explicit ILogger(LogLevel level, QObject *parent = nullptr);
    virtual ~ILogger() {}

    LogLevel GetLogLevel() const { return _level; }
    void SetLogLevel(LogLevel level) { _level = level; }
    virtual void WriteDebug(QString const &message) = 0;
    virtual void WriteDebug(LoggerCategory const &category, QString const &message) = 0;
    virtual void WriteDebugFormat(QString const &format, ...) = 0;
    virtual void WriteDebugFormat(LoggerCategory const &category, QString const &format, ...) = 0;
    virtual void WriteInfo(QString const &message) = 0;
    virtual void WriteInfo(LoggerCategory const &category, QString const &message) = 0;
    virtual void WriteInfoFormat(QString const &message, ...) = 0;
    virtual void WriteInfoFormat(LoggerCategory const &category, QString const &message, ...) = 0;
    virtual void WriteWarning(QString const &message) = 0;
    virtual void WriteWarning(LoggerCategory const &category, QString const &message) = 0;
    virtual void WriteWarningFormat(QString const &message, ...) = 0;
    virtual void WriteWarningFormat(LoggerCategory const &category, QString const &message, ...) = 0;
    virtual void WriteError(QString const &message) = 0;
    virtual void WriteError(LoggerCategory const &category, QString const &message) = 0;
    virtual void WriteErrorFormat(QString const &message, ...) = 0;
    virtual void WriteErrorFormat(LoggerCategory const &category, QString const &message, ...) = 0;
    virtual void WriteCritical(QString const &message) = 0;
    virtual void WriteCritical(LoggerCategory const &category, QString const &message) = 0;
    virtual void WriteCriticalFormat(QString const &message, ...) = 0;
    virtual void WriteCriticalFormat(LoggerCategory const &category, QString const &message, ...) = 0;
private:
    LogLevel _level;
};

ILogger::ILogger(LogLevel level, QObject *parent) :
    QObject(parent),
    _level(level)
{
}

}

