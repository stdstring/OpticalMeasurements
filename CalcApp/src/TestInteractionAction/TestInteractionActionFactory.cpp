#include <QMultiMap>
#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
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

QString TestInteractionActionFactory::GetType()
{
    return "TestInteractionAction";
}

ActionPtr TestInteractionActionFactory::Create(QString const &name, QMultiMap<QString, QString> const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    const QString keyName = "key";
    QList<QString> keyData = args.values(keyName);
    if (keyData.size() != 1)
        throw std::invalid_argument(keyName.toStdString());
    QString key = keyData[0];
    ComponentStoragePtr storage = serviceLocator.get()->GetStorage();
    MainConfigPtr config = serviceLocator.get()->GetConfig();
    return ActionPtr(new TestInteractionAction(name, key, storage.get()->GetTransport(), config.get()->Transport, context));
}

}
