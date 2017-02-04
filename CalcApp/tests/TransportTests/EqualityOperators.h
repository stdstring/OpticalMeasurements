#pragma once

#include "Message.h"
#include "MessageInfo.h"

namespace CalcApp
{

// TODO (std_string) : move into common library
bool operator ==(const MessageInfo &left, const MessageInfo &right);
// TODO (std_string) : move into common library
bool operator ==(const Message &left, const Message &right);

}
