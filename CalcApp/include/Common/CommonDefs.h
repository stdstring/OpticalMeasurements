#pragma once

#include <QDataStream>
#include <QMetaType>

#include <memory>

namespace CalcApp
{

// forward definitions
class ComponentStorage;
class Context;
class ExecutionContext;
class IAction;
class IActionFactory;
class IContextItem;
class ILogger;
class ITransport;
class MainConfig;
class Message;
class ServiceLocator;
class TransportConfig;

// ptr definitions
typedef std::shared_ptr<ComponentStorage> ComponentStoragePtr;
typedef std::shared_ptr<Context> ContextPtr;
typedef std::shared_ptr<ExecutionContext> ExecutionContextPtr;
typedef std::shared_ptr<IAction> ActionPtr;
typedef std::shared_ptr<IContextItem> ContextItemPtr;
typedef std::shared_ptr<ILogger> LoggerPtr;
typedef std::shared_ptr<ITransport> TransportPtr;
typedef std::shared_ptr<MainConfig> MainConfigPtr;
typedef std::shared_ptr<Message> MessagePtr;
typedef std::shared_ptr<ServiceLocator> ServiceLocatorPtr;

// serialization definitions
constexpr QDataStream::Version DataStreamVersion = QDataStream::Version::Qt_5_9;

}

Q_DECLARE_METATYPE(CalcApp::MessagePtr);
