#include <QObject>
#include <QRegExp>
#include <QString>
#include <QStringList>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestPartDataConsumerAction.h"
#include "TestPartDataConsumerActionFactory.h"

namespace CalcApp
{

TestPartDataConsumerActionFactory::TestPartDataConsumerActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestPartDataConsumerActionFactory::GetType()
{
    return "TestPartDataConsumerAction";
}

ActionPtr TestPartDataConsumerActionFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    const int argsCount = 2;
    QStringList argsList = args.split(QRegExp("\\s+"));
    if (argsList.size() != argsCount)
        throw std::invalid_argument("args");
    QString key = argsList[0];
    QString filename = argsList[1];
    return ActionPtr(new TestPartDataConsumerAction(name, key, filename, context));
}

}
