#include <QObject>
#include <QString>
//#include <QtGlobal>

#include <memory>

#include "Common/Context.h"
#include "Common/IActionFactory.h"
#include "Common/NotImplementedException.h"
#include "Common/ServiceLocator.h"
#include "TestFailedAction.h"
#include "TestFailedActionFactory.h"

namespace CalcApp
{

TestFailedActionFactory::TestFailedActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestFailedActionFactory::GetId()
{
    return "TestFailedAction";
}

std::shared_ptr<IAction> TestFailedActionFactory::Create(QString const &name, QString const &args, ServiceLocator const &serviceLocator, std::shared_ptr<Context> context)
{
    Q_UNUSED(name);
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    Q_UNUSED(context);
    throw NotImplementedException();
    //int time = args.toInt();
    //return new TestFailedAction(name, time, parent);
}

}
