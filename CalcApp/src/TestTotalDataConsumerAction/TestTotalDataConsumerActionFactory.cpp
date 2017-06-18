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
#include "TestTotalDataConsumerAction.h"
#include "TestTotalDataConsumerActionFactory.h"

namespace CalcApp
{

TestTotalDataConsumerActionFactory::TestTotalDataConsumerActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestTotalDataConsumerActionFactory::GetType()
{
    return "TestTotalDataConsumerAction";
}

ActionPtr TestTotalDataConsumerActionFactory::Create(QString const &name,
                                                     QMultiMap<QString, QString> const &args,
                                                     ServiceLocatorPtr serviceLocator,
                                                     ContextPtr context,
                                                     ExecutionStatePtr state)
{
    const QString keyName = "key";
    const QString filenameName = "filename";
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    QList<QString> keyData = args.values(keyName);
    if (keyData.size() != 1)
        throw std::invalid_argument(keyName.toStdString());
    QString key = keyData[0];
    QList<QString> filenameData = args.values(filenameName);
    if (filenameData.size() != 1)
        throw std::invalid_argument(filenameName.toStdString());
    QString filename = filenameData[0];
    return ActionPtr(new TestTotalDataConsumerAction(name, key, filename, context, state));
}

}
