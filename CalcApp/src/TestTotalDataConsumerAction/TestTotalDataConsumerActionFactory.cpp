#include <QObject>
//#include <QRegExp>
#include <QString>
//#include <QStringList>

//#include <stdexcept>

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

QString TestTotalDataConsumerActionFactory::GetId()
{
    return "TestTotalDataConsumerAction";
}

ActionPtr TestTotalDataConsumerActionFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    /*const int argsCount = 3;
    QStringList argsList = args.split(QRegExp("\\s+"));
    if (argsList.size() != argsCount)
        throw std::invalid_argument("args");
    QString key = argsList[0];
    bool ok;
    int sleepTime = argsList[1].toInt(&ok);
    if (!ok)
        throw std::invalid_argument("sleep time");
    int dataCount = argsList[2].toInt(&ok);
    if (!ok)
        throw std::invalid_argument("data count");*/
    return ActionPtr(new TestTotalDataConsumerAction(name, context));
}

}
