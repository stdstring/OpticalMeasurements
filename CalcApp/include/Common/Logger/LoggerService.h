#pragma once

#include <QObject>
#include <QString>
#include <QThread>

#include <memory>

#include "ILogger.h"

namespace CalcApp
{

class LoggerServiceWorker : public QObject
{
    Q_OBJECT
public:
    LoggerServiceWorker(std::shared_ptr<ILogger> logger);

private:
    std::shared_ptr<ILogger> _logger;

signals:
    void WriteDebug(const QString &message);
    void WriteDebug(const LoggerCategory &category, const QString &message);
    void WriteInfo(const QString &message);
    void WriteInfo(const LoggerCategory &category, const QString &message);
    void WriteWarning(const QString &message);
    void WriteWarning(const LoggerCategory &category, const QString &message);
    void WriteError(const QString &message);
    void WriteError(const LoggerCategory &category, const QString &message);

private slots:
    void ProcessWriteDebug(const QString &message);
    void ProcessWriteDebug(const LoggerCategory &category, const QString &message);
    void ProcessWriteInfo(const QString &message);
    void ProcessWriteInfo(const LoggerCategory &category, const QString &message);
    void ProcessWriteWarning(const QString &message);
    void ProcessWriteWarning(const LoggerCategory &category, const QString &message);
    void ProcessWriteError(const QString &message);
    void ProcessWriteError(const LoggerCategory &category, const QString &message);
};

class LoggerService : public ILogger
{
public:
    LoggerService(std::shared_ptr<ILogger> logger, QObject *parent = nullptr);
    ~LoggerService();

    virtual void WriteDebug(const QString &message) override;
    virtual void WriteDebug(const LoggerCategory &category, const QString &message) override;
    virtual void WriteInfo(const QString &message) override;
    virtual void WriteInfo(const LoggerCategory &category, const QString &message) override;
    virtual void WriteWarning(const QString &message) override;
    virtual void WriteWarning(const LoggerCategory &category, const QString &message) override;
    virtual void WriteError(const QString &message) override;
    virtual void WriteError(const LoggerCategory &category, const QString &message) override;

private:
    std::shared_ptr<LoggerServiceWorker> _worker;
    std::shared_ptr<QThread> _workerThread;
};

}
