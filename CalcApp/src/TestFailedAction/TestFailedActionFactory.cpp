#include <QObject>
#include <QString>
#include <QtGlobal>

#include "Common/IActionFactory.h"
#include "Common/ITransportFactory.h"
#include "Common/MainConfig.h"
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

IAction* TestFailedActionFactory::Create(QString const &name, QString const &args, MainConfig const &config, ITransportFactory *transportFactory, QObject *parent)
{
    Q_UNUSED(config);
    Q_UNUSED(transportFactory);
    int time = args.toInt();
    return new TestFailedAction(name, time, parent);
}

}
