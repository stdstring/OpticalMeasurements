#include <QObject>
#include <QRegExp>
#include <QString>
#include <QStringList>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestTotalDataConsumerAction.h"
#include "TestTotalDataConsumerActionFactory.h"

namespace CalcApp
{

TestTotalDataConsumerActionFactory::TestTotalDataConsumerActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestTotalDataConsumerActionFactory::GetType()
{
    return "TestTotalDataConsumerAction";
}

ActionPtr TestTotalDataConsumerActionFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    const int argsCount = 2;
    QStringList argsList = args.split(QRegExp("\\s+"));
    if (argsList.size() != argsCount)
        throw std::invalid_argument("args");
    QString key = argsList[0];
    QString filename = argsList[1];
    return ActionPtr(new TestTotalDataConsumerAction(name, key, filename, context));
}

}
