#pragma once

#include <cstddef>

namespace CalcApp
{

class ControlMessage
{
public:
    ControlMessage(size_t size, unsigned char* buffer) : _size(size), _buffer(buffer) {}
    size_t GetSize() const { return _size; }
    unsigned char* GetBuffer() const { return _buffer; }

    ControlMessage() = delete;
    ControlMessage(ControlMessage const&) = delete;
    ControlMessage(ControlMessage&&) = delete;
    ControlMessage& operator=(ControlMessage const&) = delete;
    ControlMessage& operator=(ControlMessage&&) = delete;

private:
    size_t _size;
    unsigned char *_buffer;
};

}
