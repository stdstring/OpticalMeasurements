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
#include "TestTotalDataFailedAction.h"
#include "TestTotalDataFailedActionFactory.h"

namespace CalcApp
{

TestTotalDataFailedActionFactory::TestTotalDataFailedActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestTotalDataFailedActionFactory::GetType()
{
    return "TestTotalDataFailedAction";
}

ActionPtr TestTotalDataFailedActionFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(serviceLocator);
    const int argsCount = 3;
    QStringList argsList = args.split(QRegExp("\\s+"));
    if (argsList.size() != argsCount)
        throw std::invalid_argument("args");
    QString sourceKey = argsList[0];
    QString destKey = argsList[1];
    bool ok;
    int failedIteration = argsList[2].toInt(&ok);
    if (!ok)
        throw std::invalid_argument("failed iteration");
    return ActionPtr(new TestTotalDataFailedAction(name, sourceKey, destKey, failedIteration, context));
}

}
