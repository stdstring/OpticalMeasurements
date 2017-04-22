#include <QObject>
#include <QString>
#include <QtGlobal>

#include "Common/IActionFactory.h"
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

IAction* TestFailedActionFactory::Create(QString const &name, QString const &args, const ServiceLocator &serviceLocator, QObject *parent)
{
    Q_UNUSED(serviceLocator);
    int time = args.toInt();
    return new TestFailedAction(name, time, parent);
}

}
