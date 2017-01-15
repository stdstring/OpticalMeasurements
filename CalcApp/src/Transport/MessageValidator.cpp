#include "MessageInfo.h"
#include "MessageValidator.h"

namespace CalcApp
{

MessageValidationResult IsMessageValid(MessageInfo const &currentMessage, MessageInfo const &prevMessage)
{
    if (currentMessage.GetPackageNumber() == (prevMessage.GetPackageNumber() + 1))
        return MessageValidationResult::PROCESS;
    if (currentMessage.GetPackageNumber() <= prevMessage.GetPackageNumber())
        return MessageValidationResult::SKIP;
    return MessageValidationResult::DELAY;
}

}
