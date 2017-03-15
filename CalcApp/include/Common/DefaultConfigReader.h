#pragma once

#include <QObject>

#include "IConfigReader.h"
#include "MainConfig.h"

namespace CalcApp
{

// TODO (std_string) : think about moving this into MainApp project
class DefaultConfigReader : public IConfigReader
{
    Q_OBJECT
public:
    explicit DefaultConfigReader(QObject *parent = nullptr);
    virtual MainConfig Read(int argc, char *argv[]) override;
};

}
