#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Utils/ActionArgumentsHelper.h"
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
    QString key = GetStringArgValue(args, keyName);
    QString filename = GetStringArgValue(args, filenameName);
    return ActionPtr(new SaveVertexDataAction(name, key, filename, context, state));
}

}
