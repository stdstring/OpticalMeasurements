#pragma once

#include <QList>
#include <QString>

#include <tuple>

#include "Common/CommonDefs.h"
#include "TestServerCore/TestServerConfig.h"

namespace CalcApp
{

std::tuple<TestServerConfig, QList<MessagePtr>> ReadConfig(QString const &filename);

}
