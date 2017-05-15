#pragma once

#include <QMetaType>
#include <QString>

namespace CustomSignalData
{

class CustomMessageData
{
public:
    CustomMessageData();
    CustomMessageData(CustomMessageData const &other);
    ~CustomMessageData();
    CustomMessageData(int value1, QString value2);

    int Value1;
    QString Value2;
};

}

Q_DECLARE_METATYPE(CustomSignalData::CustomMessageData);
