#include <QDataStream>
#include <QIODevice>

#include "Message.h"
#include "MessageInfo.h"
#include "MessageInfoFactory.h"

namespace CalcApp
{

MessageInfo CreateMessageInfo(Message const &message)
{
    // TODO (std_string) : we will correct this minimal deserialization here
    // Min deserialization:
    // 1) quint32 with package number
    // 2) quint32 with calculation number
    // 3) other data
    quint32 packageNumber, calcNumber;
    QDataStream stream(message.GetData());
    stream.setVersion(QDataStream::Qt_5_5);
    stream >> packageNumber >> calcNumber;
    return MessageInfo(packageNumber, calcNumber);
}

}
