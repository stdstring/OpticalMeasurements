#pragma once

#include <memory>

#include "ComponentStorage.h"
#include "ILogger.h"
#include "MainConfig.h"

namespace CalcApp
{

class ServiceLocator
{
public:
    ServiceLocator(std::shared_ptr<MainConfig> config,
                   std::shared_ptr<ComponentStorage> storage,
                   std::shared_ptr<ILogger> logger);

    std::shared_ptr<MainConfig> GetConfig() const;
    std::shared_ptr<ComponentStorage> GetStorage() const;
    std::shared_ptr<ILogger> GetLogger() const;

private:
    std::shared_ptr<MainConfig> _config;
    std::shared_ptr<ComponentStorage> _storage;
    std::shared_ptr<ILogger> _logger;
};

}
