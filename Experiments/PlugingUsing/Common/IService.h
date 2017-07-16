#include <QObject>

#pragma once

namespace PlugingUsing
{

class IService : public QObject
{
    Q_OBJECT
public:
    explicit IService(QObject *parent = nullptr) : QObject(parent) {}
    virtual void DoIt() = 0;
};

}
