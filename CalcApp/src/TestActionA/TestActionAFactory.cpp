#include <QObject>
#include <QString>
#include <QtGlobal>

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

IAction* TestActionAFactory::Create(QString const &name, QString const &args, ServiceLocator const & serviceLocator, QObject *parent)
{
    Q_UNUSED(serviceLocator);
    int time = args.toInt();
    return new TestActionA(name, time, parent);
}

}
