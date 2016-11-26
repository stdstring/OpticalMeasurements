#pragma once

#include <QString>

namespace CalcApp
{

class MainAppConfig
{
public:
    MainAppConfig(QString const &transportLocation, QString const &calculatorLocation) :
        _transportLocation(transportLocation),
        _calculatorLocation(calculatorLocation)
    {
    }

    QString const& GetTransportLocation() const { return _transportLocation; }
    QString const& GetCalculatorLocation() const { return _calculatorLocation; }

    MainAppConfig() = delete;
    MainAppConfig(MainAppConfig const&) = delete;
    MainAppConfig(MainAppConfig&&) = delete;
    MainAppConfig& operator=(MainAppConfig const&) = delete;
    MainAppConfig& operator=(MainAppConfig&&) = delete;

private:
    QString _transportLocation;
    QString _calculatorLocation;
};

}
