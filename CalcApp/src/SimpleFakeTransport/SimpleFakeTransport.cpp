#include <QObject>

#include <exception>

#include "../CommonLib/ControlMessage.h"
#include "../CommonLib/DataMessage.h"
#include "SimpleFakeTransport.h"

namespace CalcApp
{

ControlMessage SimpleFakeTransport::ProcessControlCmd(ControlMessage const &request)
{
    throw std::logic_error("not implemented");
}

bool SimpleFakeTransport::HasEvents() const
{
    return false;
}

ControlMessage SimpleFakeTransport::RetrieveEvent()
{
    throw std::logic_error("not implemented");
}

bool SimpleFakeTransport::HasData() const
{
    return false;
}

DataMessage SimpleFakeTransport::RetrieveData()
{
    throw std::logic_error("not implemented");
}

}
