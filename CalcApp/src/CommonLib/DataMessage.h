#pragma once

#include <QByteArray>

namespace CalcApp
{

class DataMessage
{
public:
    DataMessage(int packetNumber, QByteArray &&data) : _packetNumber(packetNumber),  _data(data) {}
    int GetPacketNumber() const { return _packetNumber; }
    QByteArray const& GetData() const { return _data; }

    DataMessage() = delete;
    DataMessage(DataMessage const&) = delete;
    DataMessage(DataMessage&&) = delete;
    DataMessage& operator=(DataMessage const&) = delete;
    DataMessage& operator=(DataMessage&&) = delete;

private:
    int _packetNumber;
    QByteArray _data;
};

}
