#pragma once

#include <QList>
#include <QObject>

#include "Common/CommonDefs.h"
#include "Common/ITransport.h"

namespace CalcApp
{

class TransportSignalHandler : public QObject
{
    Q_OBJECT
public:
    TransportSignalHandler(ITransport *transport, QObject *parent = nullptr);
    QList<MessagePtr> Messages;
    bool DataProcessFailed;
};

}
