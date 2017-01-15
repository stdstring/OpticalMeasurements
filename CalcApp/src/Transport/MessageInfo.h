#pragma once

#include <QPair>

#include "Message.h"

namespace CalcApp
{

class MessageInfo
{
public:
    MessageInfo(int packageNumber, int calcNumber) :
        _packageNumber(packageNumber),
        _calcNumber(calcNumber)
    {
    }

    int GetPackageNumber() const { return _packageNumber; }
    // TODO (std_string) : think about this
    int GetCalcNumber() const { return _calcNumber; }

    MessageInfo() = delete;
    //MessageInfo(MessageInfo const&) = delete;
    //MessageInfo(MessageInfo&&) = delete;
    //MessageInfo& operator=(MessageInfo const&) = delete;
    //MessageInfo& operator=(MessageInfo&&) = delete;

private:
    int _packageNumber;
    // TODO (std_string) : think about this
    int _calcNumber;
};

typedef QPair<MessageInfo, Message> MessageData;

}
