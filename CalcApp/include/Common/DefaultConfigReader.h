#pragma once

#include <QObject>

#include "IConfigReader.h"
#include "MainConfig.h"

namespace CalcApp
{

class DefaultConfigReader : public IConfigReader
{
    Q_OBJECT
public:
    explicit DefaultConfigReader(QObject *parent = nullptr);
    virtual MainConfig Read(int argc, char *argv[]) override;
};

}
