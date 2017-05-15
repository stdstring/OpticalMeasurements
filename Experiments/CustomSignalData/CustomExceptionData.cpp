#include <exception>

#include "CustomExceptionData.h"

namespace CustomSignalData
{

CustomExceptionData::CustomExceptionData()
{
}

CustomExceptionData::CustomExceptionData(CustomExceptionData const &other) : Exception(other.Exception)
{
}

CustomExceptionData::~CustomExceptionData()
{
}

CustomExceptionData::CustomExceptionData(std::exception_ptr exception) : Exception(exception)
{
}

}
