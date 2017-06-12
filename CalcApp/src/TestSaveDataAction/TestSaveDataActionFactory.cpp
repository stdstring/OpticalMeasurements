#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
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

ActionPtr TestSaveDataActionFactory::Create(QString const &name, const QMultiMap<QString, QString> &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    const QString keyName = "key";
    const QString filenameName = "filename";
    Q_UNUSED(serviceLocator);
    QList<QString> keyData = args.values(keyName);
    if (keyData.size() != 1)
        throw std::invalid_argument(keyName.toStdString());
    QString key = keyData[0];
    QList<QString> filenameData = args.values(filenameName);
    if (filenameData.size() != 1)
        throw std::invalid_argument(filenameName.toStdString());
    QString filename = filenameData[0];
    return ActionPtr(new TestSaveDataAction(name, key, filename, context));
}

}
