#include <QObject>
#include <QString>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestSaveDataAction.h"

namespace CalcApp
{

TestSaveDataAction::TestSaveDataAction(QString const &name, QObject *parent) :
    IAction(parent),
    _name(name)
{
}

QString TestSaveDataAction::GetName()
{
    return _name;
}

void TestSaveDataAction::Run(Context &context)
{
}

}

