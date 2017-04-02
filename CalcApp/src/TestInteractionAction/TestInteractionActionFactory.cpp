#include <QObject>
#include <QString>
#include <QtGlobal>

#include "Common/IActionFactory.h"
#include "Common/ITransportFactory.h"
#include "Common/MainConfig.h"
#include "TestInteractionAction.h"
#include "TestInteractionActionFactory.h"

namespace CalcApp
{

TestInteractionActionFactory::TestInteractionActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestInteractionActionFactory::GetId()
{
    return "TestInteractionAction";
}

IAction* TestInteractionActionFactory::Create(QString const &name, QString const &args, MainConfig const &config, ITransportFactory *transportFactory, QObject *parent)
{
    return new TestInteractionAction(name, args, transportFactory, config.Transport, parent);
}

}
