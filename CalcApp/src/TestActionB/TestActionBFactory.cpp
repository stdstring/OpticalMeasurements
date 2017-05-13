#include <QObject>
#include <QString>

#include <memory>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestActionB.h"
#include "TestActionBFactory.h"

namespace CalcApp
{

TestActionBFactory::TestActionBFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestActionBFactory::GetId()
{
    return "TestActionB";
}

std::shared_ptr<IAction> TestActionBFactory::Create(QString const &name, QString const &args, ServiceLocator const &serviceLocator, std::shared_ptr<Context> context)
{
    Q_UNUSED(serviceLocator);
    int time = args.toInt();
    return std::shared_ptr<IAction>(new TestActionB(name, time, context));
}

}
