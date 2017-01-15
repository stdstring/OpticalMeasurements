#pragma once

#include "MessageInfo.h"

namespace CalcApp
{

enum MessageValidationResult { PROCESS, DELAY, SKIP };

MessageValidationResult IsMessageValid(MessageInfo const &currentMessage, MessageInfo const &prevMessage);

}
