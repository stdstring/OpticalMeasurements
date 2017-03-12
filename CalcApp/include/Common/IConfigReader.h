#pragma once

#include <QObject>

#include "MainConfig.h"

namespace CalcApp
{

class IConfigReader : public QObject
{
    Q_OBJECT
public:
    explicit IConfigReader(QObject *parent = nullptr) : QObject(parent) {}
    virtual MainConfig Read(int argc, char *argv[]) = 0;
};

}
