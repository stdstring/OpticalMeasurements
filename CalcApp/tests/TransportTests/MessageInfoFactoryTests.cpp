#include <QByteArray>

#include "gtest/gtest.h"

#include "Message.h"
#include "MessageInfo.h"
#include "MessageInfoFactory.h"

namespace CalcApp
{

/*// TODO (std_string) : move into common library
bool operator ==(const MessageInfo &left, const MessageInfo &right)
{
    return (left.GetPackageNumber() == right.GetPackageNumber()) && (left.GetCalcNumber() == right.GetCalcNumber());
}*/

TEST(MessageInfoFactoryTests, Create)
{
    //ASSERT_EQ(MessageInfo(0, 0), CreateMessageInfo(Message(MessageType::DATA, QByteArray())));
}

}
