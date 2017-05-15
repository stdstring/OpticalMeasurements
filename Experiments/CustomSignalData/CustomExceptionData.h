#pragma once

#include <exception>

#include <QMetaType>

namespace CustomSignalData
{

class CustomExceptionData
{
public:
    CustomExceptionData();
    CustomExceptionData(CustomExceptionData const &other);
    ~CustomExceptionData();
    explicit CustomExceptionData(std::exception_ptr exception);

    std::exception_ptr Exception;
};

}

Q_DECLARE_METATYPE(CustomSignalData::CustomExceptionData);
