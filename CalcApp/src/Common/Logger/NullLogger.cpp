#include <QObject>
#include <QString>

#include "ILogger.h"
#include "NullLogger.h"

namespace CalcApp
{

NullLogger::NullLogger(QObject *parent) : ILogger(parent)
{
}

void NullLogger::WriteDebug(QString const &message)
{
    Q_UNUSED(message);
}

void NullLogger::WriteDebug(LoggerCategory const &category, QString const &message)
{
    Q_UNUSED(category);
    Q_UNUSED(message);
}

/*void NullLogger::WriteDebugFormat(QString const &format, ...)
{
}

void NullLogger::WriteDebugFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

void NullLogger::WriteInfo(QString const &message)
{
    Q_UNUSED(message);
}

void NullLogger::WriteInfo(LoggerCategory const &category, QString const &message)
{
    Q_UNUSED(category);
    Q_UNUSED(message);
}

/*void NullLogger::WriteInfoFormat(QString const &format, ...)
{
}

void NullLogger::WriteInfoFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

void NullLogger::WriteWarning(QString const &message)
{
    Q_UNUSED(message);
}

void NullLogger::WriteWarning(LoggerCategory const &category, QString const &message)
{
    Q_UNUSED(category);
    Q_UNUSED(message);
}

/*void NullLogger::WriteWarningFormat(QString const &format, ...)
{
}

void NullLogger::WriteWarningFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

void NullLogger::WriteError(QString const &message)
{
    Q_UNUSED(message);
}

void NullLogger::WriteError(LoggerCategory const &category, QString const &message)
{
    Q_UNUSED(category);
    Q_UNUSED(message);
}

/*void NullLogger::WriteErrorFormat(QString const &format, ...)
{
}

void NullLogger::WriteErrorFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

/*void NullLogger::WriteCritical(QString const &message)
{
}

void NullLogger::WriteCritical(LoggerCategory const &category, QString const &message)
{
}

void NullLogger::WriteCriticalFormat(QString const &format, ...)
{
}

void NullLogger::WriteCriticalFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

}
