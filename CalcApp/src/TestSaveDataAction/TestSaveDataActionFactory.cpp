#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Utils/ActionArgumentsHelper.h"
#include "Common/Context.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestSaveDataAction.h"
#include "TestSaveDataActionFactory.h"

namespace CalcApp
{

TestSaveDataActionFactory::TestSaveDataActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestSaveDataActionFactory::GetType()
{
    return "TestSaveDataAction";
}

ActionPtr TestSaveDataActionFactory::Create(QString const &name,
                                            QMultiMap<QString, QString> const &args,
                                            ServiceLocatorPtr serviceLocator,
                                            ContextPtr context,
                                            ExecutionStatePtr state)
{
    const QString keyName = "key";
    const QString filenameName = "filename";
    Q_UNUSED(serviceLocator);
    QString key = GetStringArgValue(args, keyName);
    QString filename = GetStringArgValue(args, filenameName);
    return ActionPtr(new TestSaveDataAction(name, key, filename, context, state));
}

}
