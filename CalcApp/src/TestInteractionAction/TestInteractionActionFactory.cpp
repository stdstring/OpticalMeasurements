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
    Q_UNUSED(name);
    Q_UNUSED(args);
    Q_UNUSED(config);
    Q_UNUSED(transportFactory);
    Q_UNUSED(parent);
    return nullptr;
}

}
