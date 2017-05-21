#pragma once

#include <memory>

#include "CommonDefs.h"
#include "Logger/ILogger.h"
#include "ComponentStorage.h"
#include "MainConfig.h"

namespace CalcApp
{

class ServiceLocator
{
public:
    ServiceLocator(MainConfigPtr config, ComponentStoragePtr storage, std::shared_ptr<ILogger> logger);

    MainConfigPtr GetConfig() const;
    ComponentStoragePtr GetStorage() const;
    std::shared_ptr<ILogger> GetLogger() const;

private:
    MainConfigPtr _config;
    ComponentStoragePtr _storage;
    std::shared_ptr<ILogger> _logger;
};

}
