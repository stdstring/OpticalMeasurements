#pragma once

#include <QMetaType>

#include <exception>

namespace CalcApp
{

class ExceptionData
{
public:
    ExceptionData() {}
    explicit ExceptionData(std::exception_ptr exception) : Exception(exception) {}

    std::exception_ptr Exception;
};

}

Q_DECLARE_METATYPE(CalcApp::ExceptionData);
