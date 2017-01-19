#pragma once

#include <QPair>

#include "Message.h"

namespace CalcApp
{

class MessageInfo
{
public:
    MessageInfo() :
        _isEmpty(true),
        _packageNumber(0),
        _calcNumber(0)
    {
    }

    MessageInfo(int packageNumber, int calcNumber) :
        _isEmpty(false),
        _packageNumber(packageNumber),
        _calcNumber(calcNumber)
    {
    }

    bool IsEmpty() const { return _isEmpty; }
    int GetPackageNumber() const { return _packageNumber; }
    // TODO (std_string) : think about this
    int GetCalcNumber() const { return _calcNumber; }

    //MessageInfo() = delete;
    //MessageInfo(MessageInfo const&) = delete;
    //MessageInfo(MessageInfo&&) = delete;
    //MessageInfo& operator=(MessageInfo const&) = delete;
    //MessageInfo& operator=(MessageInfo&&) = delete;

private:
    // for using convenience
    bool _isEmpty;
    int _packageNumber;
    // TODO (std_string) : think about this
    int _calcNumber;
};

typedef QPair<MessageInfo, Message> MessageData;

}
