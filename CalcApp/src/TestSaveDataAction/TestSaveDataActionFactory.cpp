#include <QObject>
#include <QString>
#include <QtGlobal>

#include "Common/IActionFactory.h"
#include "Common/MainConfig.h"
#include "TestSaveDataAction.h"
#include "TestSaveDataActionFactory.h"

namespace CalcApp
{

TestSaveDataActionFactory::TestSaveDataActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestSaveDataActionFactory::GetId()
{
    return "TestSaveDataAction";
}

IAction* TestSaveDataActionFactory::Create(QString const &name, QString const &args, MainConfig const &config, QObject *parent)
{
    return nullptr;
}

}
