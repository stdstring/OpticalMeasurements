#include <QObject>
#include <QString>
#include <QtGlobal>

#include "Common/IActionFactory.h"
#include "Common/MainConfig.h"
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

IAction* TestActionAFactory::Create(QString const &name, QString const &args, MainConfig const &config, QObject *parent)
{
    Q_UNUSED(config);
    int time = args.toInt();
    return new TestActionA(name, time, parent);
}

}
