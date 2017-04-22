#pragma once

#include <memory>

#include "Logger/ILogger.h"
#include "ComponentStorage.h"
#include "MainConfig.h"

namespace CalcApp
{

// TODO (std_string) : think about this definition
class ComponentStorage;

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
