#pragma once

#include <QObject>

#include "IConfigReader.h"
#include "MainConfig.h"

namespace CalcApp
{

class DefaultConfigReader : public IConfigReader
{
public:
    explicit DefaultConfigReader(QObject *parent = 0);
    virtual MainConfig Read(int argc, char *argv[]) override;
};

}
