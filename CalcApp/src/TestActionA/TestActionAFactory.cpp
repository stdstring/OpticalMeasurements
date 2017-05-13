#include <QObject>
#include <QString>
//#include <QtGlobal>

#include <memory>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestActionA.h"
#include "TestActionAFactory.h"

namespace CalcApp
{

TestActionAFactory::TestActionAFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestActionAFactory::GetId()
{
    return "TestActionA";
}

std::shared_ptr<IAction> TestActionAFactory::Create(QString const &name, QString const &args, ServiceLocator const &serviceLocator, std::shared_ptr<Context> context)
{
    Q_UNUSED(serviceLocator);
    int time = args.toInt();
    return std::shared_ptr<IAction>(new TestActionA(name, time, context));
}

}
