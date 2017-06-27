#include <QMultiMap>
#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IActionFactory.h"
#include "Common/ComponentStorage.h"
#include "Common/MainConfig.h"
#include "Common/ServiceLocator.h"
#include "DataReceiverAction.h"
#include "DataReceiverActionFactory.h"

namespace CalcApp
{

DataReceiverActionFactory::DataReceiverActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString DataReceiverActionFactory::GetType()
{
    return "DataReceiverAction";
}

ActionPtr DataReceiverActionFactory::Create(QString const &name,
                                            QMultiMap<QString, QString> const &args,
                                            ServiceLocatorPtr serviceLocator,
                                            ContextPtr context,
                                            ExecutionStatePtr state)
{
    const QString keyName = "key";
    QList<QString> keyData = args.values(keyName);
    if (keyData.size() != 1)
        throw std::invalid_argument(keyName.toStdString());
    QString key = keyData[0];
    ComponentStoragePtr storage = serviceLocator.get()->GetStorage();
    MainConfigPtr config = serviceLocator.get()->GetConfig();
    return ActionPtr(new DataReceiverAction(name, key, context, state));
}

}
