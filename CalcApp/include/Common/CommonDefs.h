#pragma once

#include <memory>

namespace CalcApp
{

// forward definitions
class ComponentStorage;
class Context;
class IAction;
class IActionFactory;
class IContextItem;
class MainConfig;
class ServiceLocator;

// ptr definitions
typedef std::shared_ptr<ComponentStorage> ComponentStoragePtr;
typedef std::shared_ptr<Context> ContextPtr;
typedef std::shared_ptr<IAction> ActionPtr;
typedef std::shared_ptr<IContextItem> ContextItemPtr;
typedef std::shared_ptr<MainConfig> MainConfigPtr;
typedef std::shared_ptr<ServiceLocator> ServiceLocatorPtr;

}
