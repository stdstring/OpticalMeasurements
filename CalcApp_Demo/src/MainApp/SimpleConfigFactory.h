#pragma once

#include "MainAppConfig.h"

namespace CalcApp
{

class SimpleConfigFactory
{
public:
    static MainAppConfig Create(int argc, char *argv[]);

    SimpleConfigFactory() = delete;
    SimpleConfigFactory(SimpleConfigFactory const&) = delete;
    SimpleConfigFactory(SimpleConfigFactory&&) = delete;
    SimpleConfigFactory& operator=(SimpleConfigFactory const&) = delete;
    SimpleConfigFactory& operator=(SimpleConfigFactory&&) = delete;
};

}
