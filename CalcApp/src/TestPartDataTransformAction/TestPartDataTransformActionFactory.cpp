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
#include "TestPartDataTransformAction.h"
#include "TestPartDataTransformActionFactory.h"

namespace CalcApp
{

TestPartDataTransformActionFactory::TestPartDataTransformActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestPartDataTransformActionFactory::GetType()
{
    return "TestPartDataTransformAction";
}

ActionPtr TestPartDataTransformActionFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(serviceLocator);
    const int argsCount = 2;
    QStringList argsList = args.split(QRegExp("\\s+"));
    if (argsList.size() != argsCount)
        throw std::invalid_argument("args");
    QString sourceKey = argsList[0];
    QString destKey = argsList[1];
    return ActionPtr(new TestPartDataTransformAction(name, sourceKey, destKey, context));
}

}
