#pragma once

#include <QObject>

#include "Common/CommonDefs.h"

namespace CalcApp
{

class ResultProcessor : public QObject
{
public:
    explicit ResultProcessor(MainConfigPtr config, LoggerPtr logger, QObject *parent = nullptr);

    void ShowResult(ActionChainDefPtr chain);

private:
    MainConfigPtr _config;
    LoggerPtr _logger;
};

}
