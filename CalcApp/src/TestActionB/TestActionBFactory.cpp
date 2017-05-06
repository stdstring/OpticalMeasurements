#include <QObject>
#include <QString>
//#include <QtGlobal>

#include <memory>

#include "Common/Context.h"
#include "Common/IActionFactory.h"
#include "Common/NotImplementedException.h"
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
    Q_UNUSED(name);
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    Q_UNUSED(context);
    throw NotImplementedException();
    //int time = args.toInt();
    //return new TestActionB(name, time, parent);
}

}
