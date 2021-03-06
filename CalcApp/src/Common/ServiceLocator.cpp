#include "CommonDefs.h"
#include "Logger/ILogger.h"
#include "ComponentStorage.h"
#include "MainConfig.h"
#include "ServiceLocator.h"

namespace CalcApp
{

ServiceLocator::ServiceLocator(MainConfigPtr config, ComponentStoragePtr storage, LoggerPtr logger) :
    _config(config),
    _storage(storage),
    _logger(logger)
{
}

MainConfigPtr ServiceLocator::GetConfig() const
{
    return _config;
}

ComponentStoragePtr ServiceLocator::GetStorage() const
{
    return _storage;
}

LoggerPtr ServiceLocator::GetLogger() const
{
    return _logger;
}

}
