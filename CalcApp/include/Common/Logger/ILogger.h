#pragma once

#include <QObject>
#include <QString>

namespace CalcApp
{

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
    explicit ILogger(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~ILogger() {}

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
};

}

Q_DECLARE_METATYPE(CalcApp::LoggerCategory);
