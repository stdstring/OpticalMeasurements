#include <QObject>
//#include <QRegExp>
#include <QString>
//#include <QList>
//#include <QtGlobal>

//#include <stdexcept>
//#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Exception/NotImplementedException.h"
#include "Common/Context.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestSaveDataAction.h"
#include "TestSaveDataActionFactory.h"

namespace CalcApp
{

TestSaveDataActionFactory::TestSaveDataActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestSaveDataActionFactory::GetType()
{
    return "TestSaveDataAction";
}

ActionPtr TestSaveDataActionFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(name);
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    Q_UNUSED(context);
    throw NotImplementedException();
    /*// TODO (std_string) : this code isn't correct in case of presence of space characters inside of any parameters
    const int argsCount = 2;
    QStringList argsList = args.split(QRegExp("\\s+"));
    if (argsList.size() != argsCount)
        throw std::invalid_argument("args");
    QString const &contextKey = argsList[0];
    QString const &destFilename = argsList[1];
    return new TestSaveDataAction(name, contextKey, destFilename, parent);*/
}

}
