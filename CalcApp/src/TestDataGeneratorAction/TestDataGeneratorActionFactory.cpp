#include <QList>
#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestDataGeneratorAction.h"
#include "TestDataGeneratorActionFactory.h"

namespace CalcApp
{

TestDataGeneratorActionFactory::TestDataGeneratorActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestDataGeneratorActionFactory::GetType()
{
    return "TestDataGeneratorAction";
}

ActionPtr TestDataGeneratorActionFactory::Create(QString const &name,
                                                 QMultiMap<QString, QString> const &args,
                                                 ServiceLocatorPtr serviceLocator,
                                                 ContextPtr context,
                                                 ExecutionStatePtr state)
{
    const QString keyName = "key";
    const QString sleepTimeName = "sleep_time";
    const QString dataCountName = "data_count";
    Q_UNUSED(serviceLocator);
    bool ok;
    QList<QString> keyData = args.values(keyName);
    if (keyData.size() != 1)
        throw std::invalid_argument(keyName.toStdString());
    QString key = keyData[0];
    QList<QString> sleepTimeData = args.values(sleepTimeName);
    if (sleepTimeData.size() != 1)
        throw std::invalid_argument(sleepTimeName.toStdString());
    int sleepTime = sleepTimeData[0].toInt(&ok);
    if (!ok)
        throw std::invalid_argument(sleepTimeName.toStdString());
    QList<QString> dataCountData = args.values(dataCountName);
    if (dataCountData.size() != 1)
        throw std::invalid_argument(dataCountName.toStdString());
    int dataCount = dataCountData[0].toInt(&ok);
    if (!ok)
        throw std::invalid_argument(dataCountName.toStdString());
    return ActionPtr(new TestDataGeneratorAction(name, key, sleepTime, dataCount, context, state));
}

}
