#include <QObject>
#include <QString>
#include <QtGlobal>

#include <memory>

#include "Common/IActionFactory.h"
#include "Common/ComponentStorage.h"
#include "Common/MainConfig.h"
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

IAction* TestInteractionActionFactory::Create(QString const &name, QString const &args, const ServiceLocator &serviceLocator, QObject *parent)
{
    std::shared_ptr<ComponentStorage> storage = serviceLocator.GetStorage();
    std::shared_ptr<MainConfig> config = serviceLocator.GetConfig();
    return new TestInteractionAction(name, args, storage.get()->GetTransport(), config.get()->Transport, parent);
}

}
