#include <QObject>
#include <QString>
#include <QtGlobal>

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

IAction* TestActionBFactory::Create(QString const &name, QString const &args, const ServiceLocator &serviceLocator, QObject *parent)
{
    Q_UNUSED(serviceLocator);
    int time = args.toInt();
    return new TestActionB(name, time, parent);
}

}
