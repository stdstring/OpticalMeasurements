#pragma once

#include "CommonDefs.h"
#include "ComponentStorage.h"
#include "MainConfig.h"

namespace CalcApp
{

class ServiceLocator
{
public:
    ServiceLocator(MainConfigPtr config, ComponentStoragePtr storage, LoggerPtr logger);

    MainConfigPtr GetConfig() const;
    ComponentStoragePtr GetStorage() const;
    LoggerPtr GetLogger() const;

private:
    MainConfigPtr _config;
    ComponentStoragePtr _storage;
    LoggerPtr _logger;
};

}
