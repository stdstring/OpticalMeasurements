#pragma once

#include "Common/CommonDefs.h"
#include "MessageInfo.h"

#if defined(TRANSPORT_LIBRARY)
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_EXPORT
#else
#define TRANSPORT_LIBRARY_DLLSPEC Q_DECL_IMPORT
#endif

namespace CalcApp
{

TRANSPORT_LIBRARY_DLLSPEC MessageInfo CreateMessageInfo(MessagePtr message);

}
