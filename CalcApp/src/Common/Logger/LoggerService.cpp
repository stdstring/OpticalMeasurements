#include <QObject>
#include <QString>
#include <QThread>

#include "Common/CommonDefs.h"
#include "ILogger.h"
#include "LoggerService.h"

namespace CalcApp
{

namespace
{

typedef void (LoggerServiceWorker::*SimpleWriteFun) (QString const&);
typedef void (LoggerServiceWorker::*CategoryWriteFun) (LoggerCategory const&, QString const&);

}

LoggerServiceWorker::LoggerServiceWorker(LoggerPtr logger) : _logger(logger)
{
    QObject::connect(this, static_cast<SimpleWriteFun>(&LoggerServiceWorker::WriteDebug), this, static_cast<SimpleWriteFun>(&LoggerServiceWorker::ProcessWriteDebug));
    QObject::connect(this, static_cast<CategoryWriteFun>(&LoggerServiceWorker::WriteDebug), this, static_cast<CategoryWriteFun>(&LoggerServiceWorker::ProcessWriteDebug));
    QObject::connect(this, static_cast<SimpleWriteFun>(&LoggerServiceWorker::WriteInfo), this, static_cast<SimpleWriteFun>(&LoggerServiceWorker::ProcessWriteInfo));
    QObject::connect(this, static_cast<CategoryWriteFun>(&LoggerServiceWorker::WriteInfo), this, static_cast<CategoryWriteFun>(&LoggerServiceWorker::ProcessWriteInfo));
    QObject::connect(this, static_cast<SimpleWriteFun>(&LoggerServiceWorker::WriteWarning), this, static_cast<SimpleWriteFun>(&LoggerServiceWorker::ProcessWriteWarning));
    QObject::connect(this, static_cast<CategoryWriteFun>(&LoggerServiceWorker::WriteWarning), this, static_cast<CategoryWriteFun>(&LoggerServiceWorker::ProcessWriteWarning));
    QObject::connect(this, static_cast<SimpleWriteFun>(&LoggerServiceWorker::WriteError), this, static_cast<SimpleWriteFun>(&LoggerServiceWorker::ProcessWriteError));
    QObject::connect(this, static_cast<CategoryWriteFun>(&LoggerServiceWorker::WriteError), this, static_cast<CategoryWriteFun>(&LoggerServiceWorker::ProcessWriteError));
}

void LoggerServiceWorker::ProcessWriteDebug(const QString &message)
{
    _logger.get()->WriteDebug(message);
}

void LoggerServiceWorker::ProcessWriteDebug(const LoggerCategory &category, const QString &message)
{
    _logger.get()->WriteDebug(category, message);
}

void LoggerServiceWorker::ProcessWriteInfo(const QString &message)
{
    _logger.get()->WriteInfo(message);
}

void LoggerServiceWorker::ProcessWriteInfo(const LoggerCategory &category, const QString &message)
{
    _logger.get()->WriteInfo(category, message);
}

void LoggerServiceWorker::ProcessWriteWarning(const QString &message)
{
    _logger.get()->WriteWarning(message);
}

void LoggerServiceWorker::ProcessWriteWarning(const LoggerCategory &category, const QString &message)
{
    _logger.get()->WriteWarning(category, message);
}

void LoggerServiceWorker::ProcessWriteError(const QString &message)
{
    _logger.get()->WriteError(message);
}

void LoggerServiceWorker::ProcessWriteError(const LoggerCategory &category, const QString &message)
{
    _logger.get()->WriteError(category, message);
}

LoggerService::LoggerService(LoggerPtr logger, QObject *parent) :
    ILogger(parent),
    _worker(new LoggerServiceWorker(logger)),
    _workerThread(new QThread())
{
    _worker.get()->moveToThread(_workerThread.get());
    _workerThread.get()->start();
}

LoggerService::~LoggerService()
{
    _workerThread.get()->exit();
    _workerThread.get()->wait();
}

void LoggerService::WriteDebug(const QString &message)
{
    emit _worker.get()->WriteDebug(message);
}

void LoggerService::WriteDebug(const LoggerCategory &category, const QString &message)
{
    emit _worker.get()->WriteDebug(category, message);
}

void LoggerService::WriteInfo(const QString &message)
{
    emit _worker.get()->WriteInfo(message);
}

void LoggerService::WriteInfo(const LoggerCategory &category, const QString &message)
{
    emit _worker.get()->WriteInfo(category, message);
}

void LoggerService::WriteWarning(const QString &message)
{
    emit _worker.get()->WriteWarning(message);
}

void LoggerService::WriteWarning(const LoggerCategory &category, const QString &message)
{
    emit _worker.get()->WriteWarning(category, message);
}

void LoggerService::WriteError(const QString &message)
{
    emit _worker.get()->WriteError(message);
}

void LoggerService::WriteError(const LoggerCategory &category, const QString &message)
{
    emit _worker.get()->WriteError(category, message);
}

}
