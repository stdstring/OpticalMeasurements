#pragma once

#include <QtPlugin>

namespace CalcApp
{

enum ComponentType { ACTION, TRANSPORT };

class IComponentInfo
{
public:
    virtual ComponentType GetComponentType() = 0;
};

}

Q_DECLARE_INTERFACE(CalcApp::IComponentInfo, "com.stdstring.CalcApp.IComponentInfo")
