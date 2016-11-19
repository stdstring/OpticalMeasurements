#pragma once

#include <QByteArray>

namespace CalcApp
{

class ControlMessage
{
public:
    ControlMessage(QByteArray &&data) : _data(data) {}
    QByteArray const& GetData() const { return _data; }

    ControlMessage() = delete;
    ControlMessage(ControlMessage const&) = delete;
    ControlMessage(ControlMessage&&) = delete;
    ControlMessage& operator=(ControlMessage const&) = delete;
    ControlMessage& operator=(ControlMessage&&) = delete;

private:
    QByteArray &_data;
};

}
