#pragma once

#include <QCommandLineParser>
#include <QObject>

#include "Common/IConfigReader.h"
#include "Common/MainConfig.h"

namespace CalcApp
{

class DefaultConfigReader : public IConfigReader
{
    Q_OBJECT
public:
    explicit DefaultConfigReader(QObject *parent = nullptr);
    virtual MainConfig Read(QCommandLineParser *parser) override;
};

}
