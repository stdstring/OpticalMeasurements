#include <QObject>
#include <QString>
#include <QtGlobal>

#include "Common/IActionFactory.h"
#include "Common/MainConfig.h"
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

IAction* TestActionBFactory::Create(QString const &name, QString const &args, MainConfig const &config, QObject *parent)
{
    Q_UNUSED(config);
    int time = args.toInt();
    return new TestActionB(name, time, parent);
}

}
