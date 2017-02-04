#include "EqualityOperators.h"
#include "Message.h"
#include "MessageInfo.h"

namespace CalcApp
{

// TODO (std_string) : move into common library
bool operator ==(const MessageInfo &left, const MessageInfo &right)
{
    return (left.GetPackageNumber() == right.GetPackageNumber()) && (left.GetCalcNumber() == right.GetCalcNumber());
}

// TODO (std_string) : move into common library
bool operator ==(const Message &left, const Message &right)
{
    return (left.GetType() == right.GetType()) && (left.GetData() == right.GetData());
}

}
