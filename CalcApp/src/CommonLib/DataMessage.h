#pragma once

#include <cstddef>

namespace CalcApp
{

class DataMessage
{
public:
    DataMessage(int packetNumber, size_t size, unsigned char* buffer) : _packetNumber(packetNumber), _size(size), _buffer(buffer) {}
    int GetPacketNumber() const { return _packetNumber; }
    size_t GetSize() const { return _size; }
    unsigned char* GetBuffer() const { return _buffer; }

    DataMessage() = delete;
    DataMessage(DataMessage const&) = delete;
    DataMessage(DataMessage&&) = delete;
    DataMessage& operator=(DataMessage const&) = delete;
    DataMessage& operator=(DataMessage&&) = delete;

private:
    int _packetNumber;
    size_t _size;
    unsigned char *_buffer;
};

}
