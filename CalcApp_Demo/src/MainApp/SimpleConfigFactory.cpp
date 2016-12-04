#include <QString>

#include "MainAppConfig.h"
#include "SimpleConfigFactory.h"

namespace CalcApp
{

MainAppConfig SimpleConfigFactory::Create(int argc, char *argv[])
{
    QString transportLocation = "../../SimpleFakeTransport/debug/SimpleFakeTransport.dll";
    QString calculatorLocation = "../../SimpleFakeCalculator/debug/SimpleFakeCalculator.dll";
    return MainAppConfig(transportLocation, calculatorLocation);
}

}
