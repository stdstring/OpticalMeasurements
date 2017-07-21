#pragma once

#include "Common/CommonDefs.h"
#include "MessageInfo.h"

namespace CalcApp
{

// TODO (std_string) : move into common library
bool operator ==(MessageInfo const &left, MessageInfo const &right);
bool operator !=(MessageInfo const &left, MessageInfo const &right);
// TODO (std_string) : move into common library
bool operator ==(Message const &left, Message const &right);
bool operator !=(Message const &left, Message const &right);
// TODO (std_string) : move into common library
bool operator ==(MessagePtr left, MessagePtr right);
bool operator !=(MessagePtr left, MessagePtr right);

}
