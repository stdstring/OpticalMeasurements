#include <QMultiMap>
#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Utils/ActionArgumentsHelper.h"
#include "Common/IActionFactory.h"
#include "Common/ComponentStorage.h"
#include "Common/MainConfig.h"
#include "Common/ServiceLocator.h"
#include "CalibrationAction.h"
#include "CalibrationActionFactory.h"

namespace CalcApp
{

CalibrationActionFactory::CalibrationActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString CalibrationActionFactory::GetType()
{
    return "CalibrationAction";
}

ActionPtr CalibrationActionFactory::Create(QString const &name,
                                           QMultiMap<QString, QString> const &args,
                                           ServiceLocatorPtr serviceLocator,
                                           ContextPtr context,
                                           ExecutionStatePtr state)
{
}

}
