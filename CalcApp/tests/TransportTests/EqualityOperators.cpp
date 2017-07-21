#include "Common/Message.h"

#include "EqualityOperators.h"
#include "MessageInfo.h"

namespace CalcApp
{

// TODO (std_string) : move into common library
bool operator ==(MessageInfo const &left, MessageInfo const &right)
{
    return (left.GetPackageNumber() == right.GetPackageNumber()) && (left.GetCalcNumber() == right.GetCalcNumber());
}

// TODO (std_string) : move into common library
bool operator !=(MessageInfo const &left, MessageInfo const &right)
{
    return !(left == right);
}

// TODO (std_string) : move into common library
bool operator ==(Message const &left, Message const &right)
{
    return (left.GetType() == right.GetType()) && (left.GetData() == right.GetData());
}

// TODO (std_string) : move into common library
bool operator !=(Message const &left, Message const &right)
{
    return !(left == right);
}

// TODO (std_string) : move into common library
bool operator ==(MessagePtr left, MessagePtr right)
{
    return (*left.get()) == (*right.get());
}

// TODO (std_string) : move into common library
bool operator !=(MessagePtr left, MessagePtr right)
{
    return !(left == right);
}

}
