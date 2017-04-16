#pragma once

#include <QObject>
#include <QString>

namespace CalcApp
{

enum LogLevel { DEBUG = 1, INFO = 2, WARNING = 3, ERROR = 4/*, CRITICAL*/ };

struct LoggerCategory
{
public:
    LoggerCategory() {}
    LoggerCategory(QString const &category) : Category(category) {}

    QString Category;
};

class ILogger : public QObject
{
public:
    explicit ILogger(LogLevel level, QObject *parent = nullptr) : QObject(parent), _level(level) {}
    virtual ~ILogger() {}

    LogLevel GetLogLevel() const { return _level; }
    void SetLogLevel(LogLevel level) { _level = level; }
    virtual void WriteDebug(QString const &message) = 0;
    virtual void WriteDebug(LoggerCategory const &category, QString const &message) = 0;
    /*virtual void WriteDebugFormat(QString const &format, ...) = 0;
    virtual void WriteDebugFormat(LoggerCategory const &category, QString const &format, ...) = 0;*/
    virtual void WriteInfo(QString const &message) = 0;
    virtual void WriteInfo(LoggerCategory const &category, QString const &message) = 0;
    /*virtual void WriteInfoFormat(QString const &format, ...) = 0;
    virtual void WriteInfoFormat(LoggerCategory const &category, QString const &format, ...) = 0;*/
    virtual void WriteWarning(QString const &message) = 0;
    virtual void WriteWarning(LoggerCategory const &category, QString const &message) = 0;
    /*virtual void WriteWarningFormat(QString const &format, ...) = 0;
    virtual void WriteWarningFormat(LoggerCategory const &category, QString const &format, ...) = 0;*/
    virtual void WriteError(QString const &message) = 0;
    virtual void WriteError(LoggerCategory const &category, QString const &message) = 0;
    /*virtual void WriteErrorFormat(QString const &format, ...) = 0;
    virtual void WriteErrorFormat(LoggerCategory const &category, QString const &format, ...) = 0;*/
    /*virtual void WriteCritical(QString const &message) = 0;
    virtual void WriteCritical(LoggerCategory const &category, QString const &message) = 0;
    virtual void WriteCriticalFormat(QString const &format, ...) = 0;
    virtual void WriteCriticalFormat(LoggerCategory const &category, QString const &format, ...) = 0;*/
private:
    LogLevel _level;
};

}

