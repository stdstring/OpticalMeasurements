#include <memory>

#include "ComponentStorage.h"
#include "ILogger.h"
#include "MainConfig.h"
#include "ServiceLocator.h"

namespace CalcApp
{

ServiceLocator::ServiceLocator(std::shared_ptr<MainConfig> config,
                               std::shared_ptr<ComponentStorage> storage,
                               std::shared_ptr<ILogger> logger) :
    _config(config),
    _storage(storage),
    _logger(logger)
{
}

std::shared_ptr<MainConfig> ServiceLocator::GetConfig() const
{
    return _config;
}

std::shared_ptr<ComponentStorage> ServiceLocator::GetStorage() const
{
    return _storage;
}

std::shared_ptr<ILogger> ServiceLocator::GetLogger() const
{
    return _logger;
}

}
