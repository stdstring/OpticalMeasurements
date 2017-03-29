#pragma once

#include <QList>
#include <QString>

#include <tuple>

#include "Common/Message.h"
#include "TestServerCore/TestServerConfig.h"

namespace CalcApp
{

class ConfigReader
{
public:
    std::tuple<TestServerConfig, QList<Message>> Read(QString const &filename);
};

}
