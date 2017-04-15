#include <QLoggingCategory>
#include <QMessageLogger>
#include <QObject>
#include <QString>

#include <cstdarg>

#include "ILogger.h"
#include "QMessageLoggerWrapper.h"

namespace CalcApp
{

QMessageLoggerWrapper::QMessageLoggerWrapper(LogLevel level, QObject *parent) : ILogger(level, parent)
{
}

void QMessageLoggerWrapper::WriteDebug(QString const &message)
{
    QMessageLogger().debug(message.toUtf8().constData());
}

void QMessageLoggerWrapper::WriteDebug(LoggerCategory const &category, QString const &message)
{
    QLoggingCategory loggingCategory(category.Category.toUtf8().constData());
    QMessageLogger().debug(loggingCategory, message.toUtf8().constData());
}

void QMessageLoggerWrapper::WriteDebugFormat(QString const &format, ...)
{
    va_list ap;
    va_start(ap, format);
    QMessageLogger().debug(format.toUtf8().constData(), ap);
    va_end(ap);
}

void QMessageLoggerWrapper::WriteDebugFormat(LoggerCategory const &category, QString const &format, ...)
{
    QLoggingCategory loggingCategory(category.Category.toUtf8().constData());
    va_list ap;
    va_start(ap, format);
    QMessageLogger().debug(loggingCategory, format.toUtf8().constData(), ap);
    va_end(ap);
}

void QMessageLoggerWrapper::WriteInfo(QString const &message)
{
    QMessageLogger().info(message.toUtf8().constData());
}

void QMessageLoggerWrapper::WriteInfo(LoggerCategory const &category, QString const &message)
{
    QLoggingCategory loggingCategory(category.Category.toUtf8().constData());
    QMessageLogger().info(loggingCategory, message.toUtf8().constData());
}

void QMessageLoggerWrapper::WriteInfoFormat(QString const &format, ...)
{
    va_list ap;
    va_start(ap, format);
    QMessageLogger().info(format.toUtf8().constData(), ap);
    va_end(ap);
}

void QMessageLoggerWrapper::WriteInfoFormat(LoggerCategory const &category, QString const &format, ...)
{
    QLoggingCategory loggingCategory(category.Category.toUtf8().constData());
    va_list ap;
    va_start(ap, format);
    QMessageLogger().info(loggingCategory, format.toUtf8().constData(), ap);
    va_end(ap);
}

void QMessageLoggerWrapper::WriteWarning(QString const &message)
{
    QMessageLogger().warning(message.toUtf8().constData());
}

void QMessageLoggerWrapper::WriteWarning(LoggerCategory const &category, QString const &message)
{
    QLoggingCategory loggingCategory(category.Category.toUtf8().constData());
    QMessageLogger().warning(loggingCategory, message.toUtf8().constData());
}

void QMessageLoggerWrapper::WriteWarningFormat(QString const &format, ...)
{
    va_list ap;
    va_start(ap, format);
    QMessageLogger().warning(format.toUtf8().constData(), ap);
    va_end(ap);
}

void QMessageLoggerWrapper::WriteWarningFormat(LoggerCategory const &category, QString const &format, ...)
{
    QLoggingCategory loggingCategory(category.Category.toUtf8().constData());
    va_list ap;
    va_start(ap, format);
    QMessageLogger().warning(loggingCategory, format.toUtf8().constData(), ap);
    va_end(ap);
}

void QMessageLoggerWrapper::WriteError(QString const &message)
{
    QMessageLogger().critical(message.toUtf8().constData());
}

void QMessageLoggerWrapper::WriteError(LoggerCategory const &category, QString const &message)
{
    QLoggingCategory loggingCategory(category.Category.toUtf8().constData());
    QMessageLogger().critical(loggingCategory, message.toUtf8().constData());
}

void QMessageLoggerWrapper::WriteErrorFormat(QString const &format, ...)
{
    va_list ap;
    va_start(ap, format);
    QMessageLogger().critical(format.toUtf8().constData(), ap);
    va_end(ap);
}

void QMessageLoggerWrapper::WriteErrorFormat(LoggerCategory const &category, QString const &format, ...)
{
    QLoggingCategory loggingCategory(category.Category.toUtf8().constData());
    va_list ap;
    va_start(ap, format);
    QMessageLogger().critical(loggingCategory, format.toUtf8().constData(), ap);
    va_end(ap);
}

/*void QMessageLoggerWrapper::WriteCritical(QString const &message)
{
}

void QMessageLoggerWrapper::WriteCritical(LoggerCategory const &category, QString const &message)
{
}

void QMessageLoggerWrapper::WriteCriticalFormat(QString const &format, ...)
{
}

void QMessageLoggerWrapper::WriteCriticalFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

}
