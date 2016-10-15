#pragma once

#include <cstddef>

namespace CalcApp
{

// TODO (std_string) : move into separate place
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

class ITransport
{
public:
    virtual Message ProcessControlCmd(Message const &request) = 0;
    virtual bool HasData() const = 0;
    virtual Message RetrieveData() = 0;
};

}

