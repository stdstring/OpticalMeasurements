#include "Message.h"
#include "MessageInfo.h"
#include "MessageInfoFactory.h"

namespace CalcApp
{

MessageInfo CreateMessageInfo(Message const &message)
{
    // TODO (std_string) : we will make some minimal deserialization here
    return MessageInfo(0, 0);
}

}
