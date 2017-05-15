#include <QObject>

#include <exception>
#include <stdexcept>

#include "CustomExceptionData.h"
#include "CustomMessageData.h"
#include "Processor.h"

namespace CustomSignalData
{

Processor::Processor() : QObject(nullptr)
{
}

void Processor::ProcessStart()
{
}

void Processor::ProcessFirst()
{
    emit FirstSignal(CustomMessageData(666, "iddqd"));
}

void Processor::ProcessSecond()
{
    try
    {
        throw std::logic_error("some logic error");
    }
    catch (...)
    {
        std::exception_ptr exception = std::current_exception();
        emit SecondSignal(CustomExceptionData(exception));
    }
}

void Processor::ProcessFinish()
{
}

}
