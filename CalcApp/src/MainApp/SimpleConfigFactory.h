#pragma once

#include "MainAppConfig.h"

namespace CalcApp
{

class SimpleConfigFactory
{
public:
    MainAppConfig Create(int argc, char *argv[]);
};

}
