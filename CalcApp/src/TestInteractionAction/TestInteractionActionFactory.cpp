#include <QObject>
#include <QString>
//#include <QtGlobal>

#include <memory>

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

QString TestInteractionActionFactory::GetId()
{
    return "TestInteractionAction";
}

std::shared_ptr<IAction> TestInteractionActionFactory::Create(QString const &name,
                                                              QString const &args,
                                                              std::shared_ptr<ServiceLocator> serviceLocator,
                                                              std::shared_ptr<Context> context)
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
