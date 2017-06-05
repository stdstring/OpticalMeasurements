#include <QMultiMap>
#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Exception//NotImplementedException.h"
#include "Common/IActionFactory.h"
//#include "Common/ComponentStorage.h"
//#include "Common/MainConfig.h"
#include "Common/ServiceLocator.h"
#include "TestInteractionAction.h"
#include "TestInteractionActionFactory.h"

namespace CalcApp
{

TestInteractionActionFactory::TestInteractionActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestInteractionActionFactory::GetType()
{
    return "TestInteractionAction";
}

ActionPtr TestInteractionActionFactory::Create(QString const &name, QMultiMap<QString, QString> const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(name);
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    Q_UNUSED(context);
    throw NotImplementedException();
    /*std::shared_ptr<ComponentStorage> storage = serviceLocator.GetStorage();
    std::shared_ptr<MainConfig> config = serviceLocator.GetConfig();
    return new TestInteractionAction(name, args, storage.get()->GetTransport(), config.get()->Transport, parent);*/
}

}
