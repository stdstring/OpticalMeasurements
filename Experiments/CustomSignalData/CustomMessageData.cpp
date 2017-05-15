#include <QString>

#include "CustomMessageData.h"

namespace CustomSignalData
{

CustomMessageData::CustomMessageData()
{
}

CustomMessageData::CustomMessageData(CustomMessageData const &other) : Value1(other.Value1), Value2(other.Value2)
{
}

CustomMessageData::~CustomMessageData()
{
}

CustomMessageData::CustomMessageData(int value1, QString value2) : Value1(value1), Value2(value2)
{
}

}
