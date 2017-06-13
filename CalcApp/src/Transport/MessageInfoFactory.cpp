#include <QDataStream>
#include <QIODevice>

#include "Common/CommonDefs.h"
#include "Common/Message.h"
#include "MessageInfo.h"
#include "MessageInfoFactory.h"

namespace CalcApp
{

MessageInfo CreateMessageInfo(MessagePtr message)
{
    // TODO (std_string) : we will correct this minimal deserialization here
    // Min deserialization:
    // 1) quint32 with package number
    // 2) quint32 with calculation number
    // 3) other data
    quint32 packageNumber, calcNumber;
    QDataStream stream(message.get()->GetData());
    stream.setVersion(QDataStream::Qt_5_9);
    stream >> packageNumber >> calcNumber;
    return MessageInfo(packageNumber, calcNumber);
}

}
