#pragma once

#include <cstddef>

namespace CalcApp
{

class Message
{
public:
    Message(size_t size, unsigned char buffer[]) : _size(size), _buffer(buffer) {}
    size_t size() const { return _size; }
    unsigned char buffer() const { return _buffer; }

    Message() = delete;
    Message(Message const&) = delete;
    Message(Message&&) = delete;
    Message& operator=(Message const&) = delete;
    Message& operator=(Message&&) = delete;

private:
    size_t _size;
    unsigned char _buffer[];
};

}
