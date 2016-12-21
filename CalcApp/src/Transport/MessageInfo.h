#pragma once

#include "Message.h"

namespace CalcApp
{

class MessageInfo
{
public:
    /*MessageInfo(Message const &message, int packageNumber, int calcNumber) : _message(message), _packageNumber(packageNumber), _calcNumber(calcNumber)
    {
    }

    Message const& GetMessage() const { return _message; }
    int GetPackageNumber() const { return _packageNumber; }
    int GetCalcNumber() const { return _calcNumber; }

    MessageInfo() = delete;
    MessageInfo(MessageInfo const&) = delete;
    MessageInfo(MessageInfo&&) = delete;
    MessageInfo& operator=(MessageInfo const&) = delete;
    MessageInfo& operator=(MessageInfo&&) = delete;*/

    MessageInfo(int packageNumber, int calcNumber) : _packageNumber(packageNumber), _calcNumber(calcNumber)
    {
    }

    int GetPackageNumber() const { return _packageNumber; }
    // TODO (std_string) : think about this
    int GetCalcNumber() const { return _calcNumber; }

    MessageInfo() = delete;
    MessageInfo(MessageInfo const&) = delete;
    MessageInfo(MessageInfo&&) = delete;
    MessageInfo& operator=(MessageInfo const&) = delete;
    MessageInfo& operator=(MessageInfo&&) = delete;

private:
    /*Message _message;*/
    int _packageNumber;
    // TODO (std_string) : think about this
    int _calcNumber;
};

}
