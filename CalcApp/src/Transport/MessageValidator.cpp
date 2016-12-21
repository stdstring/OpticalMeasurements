#include "MessageInfo.h"
#include "MessageValidator.h"

namespace CalcApp
{

bool IsMessageValid(MessageInfo const &currentMessage, MessageInfo const &prevMessage)
{
    return currentMessage.GetPackageNumber() == (prevMessage.GetPackageNumber() + 1);
}

}
