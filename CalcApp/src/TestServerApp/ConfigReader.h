#pragma once

#include <QList>
#include <QString>

#include <tuple>

#include "Common/Message.h"
#include "TestServerCore/TestServerConfig.h"

namespace CalcApp
{

std::tuple<TestServerConfig, QList<Message>> ReadConfig(QString const &filename);

}