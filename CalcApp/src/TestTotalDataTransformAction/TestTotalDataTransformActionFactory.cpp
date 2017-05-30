#include <QObject>
#include <QRegExp>
#include <QString>
#include <QStringList>

#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestTotalDataTransformAction.h"
#include "TestTotalDataTransformActionFactory.h"

namespace CalcApp
{

TestTotalDataTransformActionFactory::TestTotalDataTransformActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestTotalDataTransformActionFactory::GetId()
{
    return "TestTotalDataTransformAction";
}

ActionPtr TestTotalDataTransformActionFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(serviceLocator);
    const int argsCount = 2;
    QStringList argsList = args.split(QRegExp("\\s+"));
    if (argsList.size() != argsCount)
        throw std::invalid_argument("args");
    QString sourceKey = argsList[0];
    QString destKey = argsList[1];
    return ActionPtr(new TestTotalDataTransformAction(name, sourceKey, destKey, context));
}

}
