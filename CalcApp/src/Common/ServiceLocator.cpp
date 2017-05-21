#include <memory>

#include "CommonDefs.h"
#include "ComponentStorage.h"
#include "ILogger.h"
#include "MainConfig.h"
#include "ServiceLocator.h"

namespace CalcApp
{

ServiceLocator::ServiceLocator(MainConfigPtr config, ComponentStoragePtr storage, std::shared_ptr<ILogger> logger) :
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

std::shared_ptr<ILogger> ServiceLocator::GetLogger() const
{
    return _logger;
}

}
