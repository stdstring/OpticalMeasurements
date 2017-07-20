#pragma once

#include "MessageInfo.h"

#if defined(TRANSPORT_LIBRARY)
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_EXPORT
#else
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_IMPORT
#endif

namespace CalcApp
{

enum MessageValidationResult { PROCESS, DELAY, SKIP };

TRANSPORT_LIBRARY_DLLSPEC MessageValidationResult IsMessageValid(MessageInfo const &currentMessage, MessageInfo const &prevMessage);

}
