#include <QObject>
#include <QString>
#include <QTextStream>

#include "ILogger.h"
#include "ConsoleLogger.h"

namespace CalcApp
{

ConsoleLogger::ConsoleLogger(QObject *parent) : ILogger(parent)
{
}

void ConsoleLogger::WriteDebug(QString const &message)
{
    QTextStream(stdout) << "[DEBUG]: " << message << endl;
}

void ConsoleLogger::WriteDebug(LoggerCategory const &category, QString const &message)
{
    QTextStream(stdout) << "[DEBUG]: " << category.Category << ": " << message << endl;
}

/*void ConsoleLogger::WriteDebugFormat(QString const &format, ...)
{
}

void ConsoleLogger::WriteDebugFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

void ConsoleLogger::WriteInfo(QString const &message)
{
    QTextStream(stdout) << "[INFO]: " << message << endl;
}

void ConsoleLogger::WriteInfo(LoggerCategory const &category, QString const &message)
{
    QTextStream(stdout) << "[INFO]: " << category.Category << ": " << message << endl;
}

/*void ConsoleLogger::WriteInfoFormat(QString const &format, ...)
{
}

void ConsoleLogger::WriteInfoFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

void ConsoleLogger::WriteWarning(QString const &message)
{
    QTextStream(stdout) << "[WARNING]: " << message << endl;
}

void ConsoleLogger::WriteWarning(LoggerCategory const &category, QString const &message)
{
    QTextStream(stdout) << "[WARNING]: " << category.Category << ": " << message << endl;
}

/*void ConsoleLogger::WriteWarningFormat(QString const &format, ...)
{
}

void ConsoleLogger::WriteWarningFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

void ConsoleLogger::WriteError(QString const &message)
{
    QTextStream(stdout) << "[ERROR]: " << message << endl;
}

void ConsoleLogger::WriteError(LoggerCategory const &category, QString const &message)
{
    QTextStream(stdout) << "[ERROR]: " << category.Category << ": " << message << endl;
}

/*void ConsoleLogger::WriteErrorFormat(QString const &format, ...)
{
}

void ConsoleLogger::WriteErrorFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

/*void ConsoleLogger::WriteCritical(QString const &message)
{
}

void ConsoleLogger::WriteCritical(LoggerCategory const &category, QString const &message)
{
}

void ConsoleLogger::WriteCriticalFormat(QString const &format, ...)
{
}

void ConsoleLogger::WriteCriticalFormat(LoggerCategory const &category, QString const &format, ...)
{
}*/

}
