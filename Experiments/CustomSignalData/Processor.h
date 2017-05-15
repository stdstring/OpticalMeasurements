#pragma once

#include <QObject>

#include "CustomExceptionData.h"
#include "CustomMessageData.h"

namespace CustomSignalData
{

class Processor : public QObject
{
    Q_OBJECT
public:
    Processor();

signals:
    void FirstSignal(CustomMessageData const &data);
    void SecondSignal(CustomExceptionData const &data);

public slots:
    void ProcessStart();
    void ProcessFirst();
    void ProcessSecond();
    void ProcessFinish();
};

}
