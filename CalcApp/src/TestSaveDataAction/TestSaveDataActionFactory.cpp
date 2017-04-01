#include <QObject>
#include <QRegExp>
#include <QString>
#include <QList>
#include <QtGlobal>

#include <stdexcept>

#include "Common/IActionFactory.h"
#include "Common/ITransportFactory.h"
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

IAction* TestSaveDataActionFactory::Create(QString const &name, QString const &args, MainConfig const &config, ITransportFactory *transportFactory, QObject *parent)
{
    Q_UNUSED(config);
    Q_UNUSED(transportFactory);
    // TODO (std_string) : this code isn't correct in case of presence of space characters inside of any parameters
    const int argsCount = 2;
    QStringList argsList = args.split(QRegExp("\\s+"));
    if (argsList.size() != argsCount)
        throw std::invalid_argument("args");
    QString const &contextKey = argsList[0];
    QString const &destFilename = argsList[1];
    return new TestSaveDataAction(name, contextKey, destFilename, parent);
}

}
