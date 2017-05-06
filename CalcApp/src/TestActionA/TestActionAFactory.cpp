#include <QObject>
#include <QString>
//#include <QtGlobal>

#include <memory>

#include "Common/Context.h"
#include "Common/IActionFactory.h"
#include "Common/NotImplementedException.h"
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
    Q_UNUSED(name);
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    Q_UNUSED(context);
    throw NotImplementedException();
    /*int time = args.toInt();
    return new TestActionA(name, time, parent);*/
}

}
