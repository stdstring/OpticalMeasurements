#pragma once

#include <QObject>

#include "MainConfig.h"

namespace CalcApp
{

class IConfigReader : public QObject
{
public:
    explicit IConfigReader(QObject *parent = nullptr) : QObject(parent) {}
    virtual MainConfig Read(int argc, char *argv[]) = 0;
};

}
