#pragma once

#include <QPair>

#include "Common/CommonDefs.h"

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

    MessageInfo(quint32 packageNumber, quint32 calcNumber) :
        _isEmpty(false),
        _packageNumber(packageNumber),
        _calcNumber(calcNumber)
    {
    }

    bool IsEmpty() const { return _isEmpty; }
    quint32 GetPackageNumber() const { return _packageNumber; }
    // TODO (std_string) : think about this
    quint32 GetCalcNumber() const { return _calcNumber; }

    //MessageInfo() = delete;
    //MessageInfo(MessageInfo const&) = delete;
    //MessageInfo(MessageInfo&&) = delete;
    //MessageInfo& operator=(MessageInfo const&) = delete;
    //MessageInfo& operator=(MessageInfo&&) = delete;

private:
    // for using convenience
    bool _isEmpty;
    quint32 _packageNumber;
    // TODO (std_string) : think about this
    quint32 _calcNumber;
};

typedef QPair<MessageInfo, MessagePtr> MessageData;

}
