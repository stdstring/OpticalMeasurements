#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "SaveVertexDataAction.h"
#include "SaveVertexDataActionFactory.h"

namespace CalcApp
{

SaveVertexDataActionFactory::SaveVertexDataActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString SaveVertexDataActionFactory::GetType()
{
    return "SaveVertexDataAction";
}

ActionPtr SaveVertexDataActionFactory::Create(QString const &name,
                                              QMultiMap<QString, QString> const &args,
                                              ServiceLocatorPtr serviceLocator,
                                              ContextPtr context,
                                              ExecutionStatePtr state)
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
    return ActionPtr(new SaveVertexDataAction(name, key, filename, context, state));
}

}
