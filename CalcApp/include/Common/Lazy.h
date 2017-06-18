#pragma once

#include <QMutex>
#include <QMutexLocker>

#include <functional>

namespace CalcApp
{

template <typename T> class Lazy
{
public:
    explicit Lazy(std::function<T()> generator) : _generator(generator), _initialized(false), _mutex(QMutex::NonRecursive) {}

    T GetValue()
    {
        if (_initialized)
            return _value;
        {
            QMutexLocker locker(&_mutex);
            if (_initialized)
                return _value;
            _value(generator());
            _initialized = true;
            return _value;
        }
    }

    bool HasValue() const { return _initialized; }

private:
    std::function<T()> _generator;
    volatile bool _initialized;
    QMutex _mutex;
    T _value;
};

}
