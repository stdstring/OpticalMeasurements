#include <QApplication>

#include "MainWindow.h"

#include "ComponentLoader.h"
#include "MainAppConfig.h"
#include "SimpleConfigFactory.h"
#include "../CommonLib/ICalculatorFactory.h"
#include "../CommonLib/ITransportFactory.h"
#include "../CommonLib/TransportConfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcApp::MainAppConfig config = CalcApp::SimpleConfigFactory::Create(argc, argv);
    CalcApp::ICalculatorFactory *calculatorFactory = CalcApp::ComponentLoader::Load<CalcApp::ICalculatorFactory>(config.GetCalculatorLocation(), &a);
    CalcApp::ITransportFactory *transportFactory = CalcApp::ComponentLoader::Load<CalcApp::ITransportFactory>(config.GetTransportLocation(), &a);
    CalcApp::TransportConfig transportConfig;
    CalcApp::ITransport *transport = transportFactory->Create(transportConfig, &a);
    CalcApp::ICalculator *calculator = calculatorFactory->Create(transport, &a);
    MainWindow w;
    QWidget *calculatorWidget = calculator->CreateCalculatorWidget(&w);
    w.show();
    return a.exec();
}
