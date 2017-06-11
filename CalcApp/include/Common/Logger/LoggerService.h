#pragma once

#include <QObject>
#include <QString>
#include <QThread>

#include <memory>

#include "Common/CommonDefs.h"
#include "ILogger.h"

namespace CalcApp
{

class LoggerServiceWorker : public QObject
{
    Q_OBJECT
public:
    LoggerServiceWorker(LoggerPtr logger);

private:
    LoggerPtr _logger;

signals:
    void WriteDebug(QString message);
    void WriteDebug(LoggerCategory category, QString message);
    void WriteInfo(QString message);
    void WriteInfo(LoggerCategory category, QString message);
    void WriteWarning(QString message);
    void WriteWarning(LoggerCategory category, QString message);
    void WriteError(QString message);
    void WriteError(LoggerCategory category, QString message);

private slots:
    void ProcessWriteDebug(QString message);
    void ProcessWriteDebug(LoggerCategory category, QString message);
    void ProcessWriteInfo(QString message);
    void ProcessWriteInfo(LoggerCategory category, QString message);
    void ProcessWriteWarning(QString message);
    void ProcessWriteWarning(LoggerCategory category, QString message);
    void ProcessWriteError(QString message);
    void ProcessWriteError(LoggerCategory category, QString message);
};

class LoggerService : public ILogger
{
public:
    LoggerService(LoggerPtr logger, QObject *parent = nullptr);
    ~LoggerService();

    virtual void WriteDebug(QString const &message) override;
    virtual void WriteDebug(LoggerCategory const &category, QString const &message) override;
    virtual void WriteInfo(QString const &message) override;
    virtual void WriteInfo(LoggerCategory const &category, QString const &message) override;
    virtual void WriteWarning(QString const &message) override;
    virtual void WriteWarning(LoggerCategory const &category, QString const &message) override;
    virtual void WriteError(QString const &message) override;
    virtual void WriteError(LoggerCategory const &category, QString const &message) override;

private:
    std::shared_ptr<LoggerServiceWorker> _worker;
    std::shared_ptr<QThread> _workerThread;
};

}
